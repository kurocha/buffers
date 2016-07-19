//
//  PackedBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "PackedBuffer.hpp"

#include <new>

namespace Buffers
{
	PackedBuffer::PackedBuffer (std::size_t size) : _size(size)
	{
	}

	PackedBuffer::~PackedBuffer ()
	{
	}

	// Data is packed at the end of the class.
	Byte * PackedBuffer::data ()
	{
		return reinterpret_cast<Byte *>(this) + sizeof(*this);
	}

	const Byte * PackedBuffer::data () const
	{
		return reinterpret_cast<const Byte *>(this) + sizeof(*this);
	}

	PackedBuffer * PackedBuffer::allocate (std::size_t size)
	{
		std::size_t total_size = sizeof(PackedBuffer) + size;
		void * data = ::operator new (total_size);
		PackedBuffer * buffer = new(data) PackedBuffer(size);

		return buffer;
	}

	std::size_t PackedBuffer::size () const
	{
		return _size;
	}

	Byte * PackedBuffer::begin ()
	{
		return data();
	}

	const Byte * PackedBuffer::begin () const
	{
		return data();
	}
}
