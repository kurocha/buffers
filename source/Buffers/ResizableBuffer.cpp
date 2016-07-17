//
//  ResizableBuffer.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "ResizableBuffer.hpp"

namespace Buffers
{
	ResizableBuffer::~ResizableBuffer()
	{
	}
	
	void ResizableBuffer::expand (std::size_t amount)
	{
		resize(size() + amount);
	}

	void ResizableBuffer::append (std::size_t size, const Byte * data)
	{
		expand(size);

		memcpy(this->end() - size, data, size);
	}
}
