//
//  MutableBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "MutableBuffer.hpp"

#include <stdexcept>
#include <cstring>

namespace Buffers
{
	MutableBuffer::~MutableBuffer()
	{
	}

	Byte & MutableBuffer::at (std::size_t index)
	{
		if (index >= size()) throw std::out_of_range("index out of bounds");
		
		return begin()[index];
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
		// count is the number of bytes to fill:
		if (count + offset > size()) throw std::out_of_range("setting bytes will overflow buffer");

		std::memset(begin() + offset, value, count);
	}

	void MutableBuffer::assign (const Byte * other_begin, const Byte * other_end, std::size_t offset)
	{
		auto other_size = other_end - other_begin;
		
		if (offset + other_size > size())
			throw std::out_of_range("assigning data will overflow buffer");
		
		std::memcpy(begin() + offset, other_begin, other_size);
	}

	void MutableBuffer::assign (const Buffer & other, std::size_t offset)
	{
		assign(other.begin(), other.end(), offset);
	}

	void MutableBuffer::assign (const Buffer & other, std::size_t other_offset, std::size_t other_size, std::size_t offset)
	{
		assign(other.begin() + other_offset, other.begin() + other_offset + other_size, offset);
	}
}
