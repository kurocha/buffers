//
//  MutableBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

#include <string>

namespace Buffers
{
	/// Read/write access to data.
	class MutableBuffer : public Buffer {
	public:
		virtual ~MutableBuffer ();

		/// Provide the const version
		using Buffer::begin;

		/// Returns the address of the first byte in the buffer.
		virtual Byte * begin () = 0;
		/// Returns the address of the last byte + 1 in the buffer.
		Byte * end ();

		/// Access data at a particular location. Range checked.
		Byte * at (std::size_t index);
		/// Access data at a particular location. Not range checked.
		Byte & operator[] (std::size_t index);

		/// Copy count copies of value into the buffer at the specified offset.
		void assign (std::size_t count, const Byte & value, std::size_t offset = 0);
		/// Copy data from another range of bytes at the specified offset.
		void assign (const Byte * other_begin, const Byte * other_end, std::size_t offset = 0);
		/// Assign data from another buffer
		void assign (const Buffer & other, std::size_t offset = 0);
		/// Copy a slice of data from another buffer
		void assign (const Buffer & other, std::size_t other_offset, std::size_t other_size, std::size_t offset = 0);
		/// Copy a c-style string into the buffer
		void assign (const char * string, std::size_t offset = 0);
		/// Copy a C++ style string into the buffer.
		void assign(const std::string string, std::size_t offset = 0);

		/// Write a specific value into the buffer at the specified offset.
		template <typename AnyT>
		std::size_t write (const AnyT & value, std::size_t offset)
		{
			assign((const Byte *)value, (const Byte *)value + sizeof(AnyT), offset);

			return offset + sizeof(AnyT);
		}
	};
}
