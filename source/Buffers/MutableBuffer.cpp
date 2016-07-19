//
//  MutableBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "MutableBuffer.hpp"

#include <cassert>
#include <cstring>

namespace Buffers
{
	MutableBuffer::~MutableBuffer()
	{
	}

	Byte * MutableBuffer::at (std::size_t index)
	{
		assert(index < size());
		return begin() + index;
	}

	Byte * MutableBuffer::end ()
	{
		return begin() + size();
	}

	Byte & MutableBuffer::operator[] (std::size_t index)
	{
		return begin()[index];
	}

	void MutableBuffer::assign (std::size_t count, const Byte & value, std::size_t offset)
	{
		assert((count + offset) <= size());

		std::memset(begin() + offset, value, count);
	}

	void MutableBuffer::assign (const Byte * other_begin, const Byte * other_end, std::size_t offset)
	{
		assert((other_end - other_begin) + offset <= size());

		std::memcpy(begin() + offset, other_begin, other_end - other_begin);
	}

	void MutableBuffer::assign (const Buffer & other, std::size_t offset)
	{
		assign(other.begin(), other.end(), offset);
	}

	void MutableBuffer::assign (const Buffer & other, std::size_t other_offset, std::size_t other_size, std::size_t offset)
	{
		assign(other.begin() + other_offset, other.begin() + other_offset + other_size, offset);
	}

	void MutableBuffer::assign (const char * string, std::size_t offset)
	{
		std::size_t size = std::strlen(string);
		assign(reinterpret_cast<const Byte *>(string), reinterpret_cast<const Byte *>(string + size), offset);
	}
	
	void MutableBuffer::assign(const std::string string, std::size_t offset)
	{
		assign(reinterpret_cast<const Byte *>(string.data()), reinterpret_cast<const Byte *>(string.data() + string.size()), offset);
	}
}
