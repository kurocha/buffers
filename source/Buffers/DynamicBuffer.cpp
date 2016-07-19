//
//  DynamicBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "DynamicBuffer.hpp"

#include <cstdlib>
#include <cassert>

namespace Buffers
{
	DynamicBuffer::DynamicBuffer () : _capacity(0), _size(0), _data(nullptr)
	{
	}

	DynamicBuffer::DynamicBuffer (std::size_t size, bool reserved) : _data(nullptr)
	{
		allocate(size);

		if (reserved == false)
			_size = size;
		else
			_size = 0;
	}
	
	DynamicBuffer::DynamicBuffer(const Buffer & buffer) : DynamicBuffer(buffer.size(), true)
	{
		this->assign(buffer);
	}
	
	DynamicBuffer & DynamicBuffer::operator=(const Buffer & buffer)
	{
		this->resize(0);
		
		this->assign(buffer);
		
		return *this;
	}
	
	DynamicBuffer::~DynamicBuffer()
	{
		deallocate();
	}

	void DynamicBuffer::allocate (std::size_t size)
	{
		if (size != _capacity) {
			_data = (Byte*)realloc(_data, size);
			assert(_data != nullptr);

			_capacity = size;
		}
	}

	void DynamicBuffer::deallocate ()
	{
		if (_data) {
			free(_data);
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	std::size_t DynamicBuffer::capacity () const
	{
		return _capacity;
	}

	std::size_t DynamicBuffer::size () const
	{
		return _size;
	}

	void DynamicBuffer::clear ()
	{
		deallocate();
	}

	void DynamicBuffer::reserve (std::size_t size)
	{
		allocate(size);
	}

	void DynamicBuffer::resize (std::size_t size)
	{
		if (size > _capacity) {
			allocate(size);
		}

		_size = size;
	}

	Byte * DynamicBuffer::begin ()
	{
		return _data;
	}

	const Byte * DynamicBuffer::begin () const
	{
		return _data;
	}
}
