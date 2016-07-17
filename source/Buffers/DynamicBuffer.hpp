//
//  DynamicBuffer.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Buffers
{
	/// A flexible read/write buffer class that can be resized.
	/// This buffer provides maximum flexibility when dealing with data which may change its size, and is almost API compatible with `std::vector<unsigned char>`, but has optimizations for data buffering. This can provide up to 30% increase in performance when dealing with a lot of data.
	class DynamicBuffer : public ResizableBuffer
	{
	public:
		/// Construct an empty buffer.
		DynamicBuffer();
		
		/// Duplicate an existing buffer:
		DynamicBuffer(const Buffer &);
		
		/// Copy an existing buffer:
		DynamicBuffer & operator=(const Buffer &);
		
		/// Construct a pre-sized buffer. If reserved is true, the size refers to capacity i.e. equivalent of calling reserve(size).
		DynamicBuffer (std::size_t size, bool reserved = false);
		
		virtual ~DynamicBuffer();
		
		virtual std::size_t capacity () const;
		
		/// The current size of the data stored in the buffer. This will always be <= capacity().
		virtual std::size_t size () const;

		/// Set the size of the buffer to 0. Capacity is not changed.
		void clear ();

		virtual void reserve (std::size_t size);
		virtual void resize (std::size_t size);

		virtual Byte * begin ();
		virtual const Byte * begin () const;
		
	private:
		std::size_t _capacity, _size;
		Byte * _data;
		
		void allocate (std::size_t size);
		void deallocate ();
	};
}
