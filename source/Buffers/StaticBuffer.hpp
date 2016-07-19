//
//  StaticBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

namespace Buffers
{
	/**
		A read-only buffer that provides access to const data, such as a c-style string.

		The buffer does not copy the data that is passed to it. Therefore, it would be unwise to pass in a dynamic pointer or other data that may be deallocated before the buffer is deallocated.

		A useful case might be if you have some data, and want to manipulate it or pass it to another function as a buffer:

			Byte data[1024]
			std::size_t size = read(data, 1024);
			StaticBuffer buffer(data, size);
			process_buffer(buffer);

		In this case, we could wrap the data up in a buffer, but we didn't have to copy the data needlessly. Using a different kind of buffer, such as DynamicBuffer, would copy the data.
	*/
	class StaticBuffer : public Buffer
	{
	public:
		StaticBuffer(const Byte * data, const std::size_t & size);
		StaticBuffer(const char * null_terminated_string, bool include_null_character = true);
		
		virtual ~StaticBuffer();
		
		virtual std::size_t size () const { return _size; }
		virtual const Byte * begin () const { return _data; }
		
	private:
		const Byte * _data;
		const std::size_t _size;
	};
}
