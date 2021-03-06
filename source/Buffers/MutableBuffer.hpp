//
//  MutableBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

namespace Buffers
{
	/// Read/write access to data.
	class MutableBuffer : public Buffer {
	public:
		virtual ~MutableBuffer ();

		/// Provide the const version
		using Buffer::begin;
		using Buffer::end;
		
		/// Returns the address of the first byte in the buffer.
		virtual Byte * begin () = 0;
		/// Returns the address of the last byte + 1 in the buffer.
		Byte * end ();

		/// Access data at a particular location. Range checked.
		Byte & at (std::size_t index);
		/// Access data at a particular location. Not range checked.
		Byte & operator[] (std::size_t index);
		
		/// Return a pointer to a given offset within the buffer.
		Byte * operator+(std::size_t offset) {
			return begin() + offset;
		}

		/// Copy count copies of value into the buffer at the specified offset.
		void assign (std::size_t count, const Byte & value, std::size_t offset = 0);
		/// Copy data from another range of bytes at the specified offset.
		void assign (const Byte * other_begin, const Byte * other_end, std::size_t offset = 0);
		/// Assign data from another buffer
		void assign (const Buffer & other, std::size_t offset = 0);
		/// Copy a slice of data from another buffer
		void assign (const Buffer & other, std::size_t other_offset, std::size_t other_size, std::size_t offset = 0);

		/// Write a specific value into the buffer at the specified offset.
		template <typename AnyT>
		std::size_t write (const AnyT & value, std::size_t offset)
		{
			auto data = reinterpret_cast<const Byte *>(&value);
			
			assign(data, data + sizeof(AnyT), offset);
			
			return offset + sizeof(AnyT);
		}
	};
}
