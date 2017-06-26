//
//  ResizableBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "ResizableBuffer.hpp"

#include <cstring>

namespace Buffers
{
	ResizableBuffer::~ResizableBuffer()
	{
	}
	
	bool ResizableBuffer::expand (std::size_t amount)
	{
		return resize(size() + amount);
	}
	
	bool ResizableBuffer::expand ()
	{
		return resize(size() * 2);
	}
	
	void ResizableBuffer::operator+= (const Buffer & buffer)
	{
		append(buffer.size(), buffer.begin());
	}

	bool ResizableBuffer::append (std::size_t size, const Byte * data)
	{
		auto offset = this->size();
		
		auto reallocated = expand(size);
		
		this->assign(data, data+size, offset);
		
		return reallocated;
	}
}
