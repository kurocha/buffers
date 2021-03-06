//
//  ResizableBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "MutableBuffer.hpp"

namespace Buffers
{
	/// A buffer that can be resized. A resizable buffer may have a capacity >= size.
	class ResizableBuffer : public MutableBuffer {
	public:
		virtual ~ResizableBuffer ();

		/// The currently allocated capacity of the buffer. Can be changed by calling reserve().
		virtual std::size_t capacity () const = 0;
		
		/// The top of the allocated buffer.
		Byte * top() {return begin() + capacity();}
		const Byte * top() const {return begin() + capacity();}

		/// Reserve/allocate more capacity if required. Will release capacity if size is smaller than current capacity.
		virtual bool reserve (std::size_t size) = 0;

		/// Change the size of the buffer. Will allocate more capacity if required.
		virtual bool resize (std::size_t size) = 0;

		/// Increase the size of the buffer by the given size.
		bool expand (std::size_t amount);
		
		/// Efficiently increase the size of the buffer by at least one.
		bool expand ();
		
		/// Appends a set number of bytes to the end of the buffer
		bool append (std::size_t size, const Byte * data);
		
		void operator+= (const Buffer & buffer);
		
		// Helper for appending primitive types.
		template <typename ObjectT>
		void append (const ObjectT & value)
		{
			append(sizeof(ObjectT), (const Byte *)&value);
		}

		/// Append data from an incremental iterator
		template <typename AnyT>
		void append (AnyT begin, AnyT end)
		{
			while (begin != end) {
				append(*begin);
				++begin;
			}
		}
	};
}
