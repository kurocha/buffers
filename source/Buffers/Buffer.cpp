//
//  Buffer.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "Buffer.hpp"
#include "File.hpp"

#include <stdexcept>
#include <cassert>
#include <cstring>
#include <sstream>

#include <sys/types.h>
#include <unistd.h>

namespace Buffers
{
	Buffer::~Buffer()
	{
	}

	const Byte * Buffer::at (std::size_t offset) const
	{
		if (offset > size()) throw std::out_of_range(__func__);
		
		return begin() + offset;
	}

	void Buffer::read (std::size_t offset, std::size_t size, Byte * value) const
	{
		assert(offset+size <= this->size());
		
		std::memcpy(value, at(offset), size);
	}

	const Byte & Buffer::operator[] (std::size_t offset) const
	{
		assert(offset <= size());
		
		return begin()[offset];
	}

	const Byte * Buffer::end () const
	{
		return begin() + size();
	}

	bool Buffer::operator== (const Buffer & other) const
	{
		if (size() != other.size())
			return false;

		// If size is the same, check data is the same
		return bcmp(begin(), other.begin(), size()) == 0;
	}

	bool Buffer::operator!= (const Buffer & other) const
	{
		return !(*this == other);
	}

	/// Dump the buffer as hex to the given stream.
	void Buffer::hexdump (std::ostream & out) const
	{
		// http://stahlforce.com/dev/index.php?tool=csc01
		const Byte * current = begin();
		std::size_t remaining = size();

		while (true) {
			std::stringstream buffer;

			buffer << "0x";

			buffer.fill('0');
			buffer.width(sizeof(long) * 2);
			buffer.setf(std::ios::hex, std::ios::basefield);

			buffer << (current - begin()) << " >";

			std::size_t count = std::min(remaining, (std::size_t)4*4);

			for (std::size_t i = 0; i < (4*4); i += 1) {
				if (i > 0 && i % 4 == 0)
					buffer << ' ';

				if (i < count) {
					buffer.width(2);
					buffer << (int)(*(current + i));
				} else
					buffer << "  ";
			}

			buffer << "< ";

			out << buffer.str();

			for (std::size_t i = 0; i < count; i += 1) {
				Byte character = *(current + i);
				if (character >= 32 && character <= 128)
					out << character;
				else
					out << ".";
			}

			out << std::endl;

			remaining -= count;
			if (remaining == 0)
				break;

			current += count;
		}
	}

	uint32_t Buffer::checksum () const {
		uint32_t sum = 0;
		uint32_t r = 55665;
		const uint32_t C1 = 52845;
		const uint32_t C2 = 22719;

		std::size_t s = size();
		const Byte * b = begin();

		for (unsigned i = 0; i < s; i += 1) {
			Byte cipher = (b[i] ^ (r >> 8));
			r = (cipher + r) * C1 + C2;
			sum += cipher;
		}

		return sum;
	}

	void Buffer::write_to_file (const std::string & path) const
	{
		File file(path, O_WRONLY|O_CREAT);

		file.write(*this);
	}
	
	void Buffer::write_to_stream (FileDescriptor file_descriptor) const
	{
		std::size_t sent = 0;

		while (sent < size()) {
			auto result = ::write(file_descriptor, begin() + sent, size() - sent);
			
			if (result < 0) {
				throw std::system_error(errno, std::system_category(), "write");
			}
			
			sent += result;
		}
	}
}
