//
//  DynamicBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "DynamicBuffer.hpp"

#include <cstdlib>
#include <cstring>
#include <memory>
#include <iostream>

namespace Buffers
{
	DynamicBuffer::DynamicBuffer ()
	{
	}
	
	DynamicBuffer::DynamicBuffer(const Buffer & other) : DynamicBuffer(other.size())
	{
		assign(other);
	}

	DynamicBuffer::DynamicBuffer (std::size_t size, bool reserved)
	{
		allocate(size);

		if (reserved == false)
			_size = size;
		else
			_size = 0;
	}
	
	// DynamicBuffer::DynamicBuffer(const Buffer & buffer) : DynamicBuffer(buffer.size(), true)
	// {
	// 	this->assign(buffer);
	// }
	
	// DynamicBuffer & DynamicBuffer::operator=(const Buffer & buffer)
	// {
	// 	this->resize(0);
	// 	
	// 	this->assign(buffer);
	// 	
	// 	return *this;
	// }
	
	DynamicBuffer::~DynamicBuffer()
	{
		deallocate();
	}

	bool DynamicBuffer::allocate (std::size_t capacity)
	{
		if (capacity != _capacity) {
			//std::cerr << "realloc(" << (void *)_data << ", " << size << ") -> ";
			auto data = (Byte*)realloc(_data, capacity);
			//std::cerr << (void *)_data << std::endl;
			
			if (data == nullptr) {
				throw std::bad_alloc();
			}
			
			_capacity = capacity;
			
			if (_data == data) {
				// data address was not changed.
				return false;
			} else {
				// data address was changed.
				_data = data;
				return true;
			}
		}
		
		//std::cerr << "done allocate(" << size << ") [capacity=" << _capacity << "]" << std::endl;
		return false;
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

	bool DynamicBuffer::reserve (std::size_t size)
	{
		if (size > _capacity) {
			return allocate(size);
		} else {
			return false;
		}
	}

	bool DynamicBuffer::resize (std::size_t size)
	{
		const std::size_t PLATEAU = 1 << 12;
		bool reallocated = false;
		
		//std::cerr << "resize(" << size << ") [capacity=" << _capacity << "]" << std::endl;
		if (size > _capacity) {
			std::size_t next_size = size * 2;
			if (next_size < 128) next_size = 128;
			
			// This helps to generate allocations that align with page boundaries.
			if (next_size > PLATEAU)
				next_size = (next_size + PLATEAU) & ~(PLATEAU - 1);
			
			if (next_size < size) throw std::runtime_error("could not compute next size");
			
			reallocated = allocate(next_size);
		}
		
		_size = size;
		
		return reallocated;
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
