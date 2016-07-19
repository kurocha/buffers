//
//  PackedBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "MutableBuffer.hpp"

namespace Buffers
{
	/**
		A fast read/write buffer that can't be resized.

		This class is similar to DynamicBuffer in the sense that it is mutable, however it is slightly more efficient for buffers that won't change size because a packed buffer will allocate its class data in line with the buffer - so the most expensive part (malloc/new) only happens at most once instead of twice or more.

		This class will copy assigned data. Therefore, you may want to consider StaticBuffer if you don't want to copy the data.
	*/
	class PackedBuffer : public MutableBuffer {
	public:
		PackedBuffer() = delete;
		virtual ~PackedBuffer ();

		PackedBuffer(const PackedBuffer & other) = delete;
		PackedBuffer & operator=(const PackedBuffer & other) = delete;

		/// Create a new buffer.
		static PackedBuffer * allocate (std::size_t size);

		virtual std::size_t size () const;

		virtual Byte * begin ();
		virtual const Byte * begin () const;
	private:
		std::size_t _size;

		PackedBuffer (std::size_t size);

		Byte * data ();
		const Byte * data () const;
	};
}
