//
//  StaticBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "StaticBuffer.hpp"

#include <cstring>

namespace Buffers
{
	StaticBuffer::StaticBuffer(const Byte * data, const std::size_t & size) : _data(data), _size(size)
	{
	}
	
	StaticBuffer::StaticBuffer(const char * null_terminated_string, bool include_null_character) : StaticBuffer(reinterpret_cast<const Byte *>(null_terminated_string), std::strlen(null_terminated_string) + (include_null_character ? 1 : 0))
	{
	}
	
	StaticBuffer::~StaticBuffer()
	{
	}
}
