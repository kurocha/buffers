//
//  Buffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Endian.hpp"

#include <cstdint>
#include <iosfwd>

namespace Buffers
{
	typedef uint8_t Byte;
	typedef int FileDescriptor;
	
	/// Read-only access to data.
	class Buffer {
	public:
		Buffer() = default;
		virtual ~Buffer ();
		
		Buffer(const Buffer & other) = delete;
		Buffer & operator=(const Buffer & other) = delete;

		/// Access data at a particular location. Range checked.
		const Byte at (std::size_t offset) const;
		
		/// Return a pointer to a given offset within the buffer.
		const Byte * operator+(std::size_t offset) const {
			return begin() + offset;
		}

		/// Read data of a given size from the buffer
		void read (std::size_t offset, std::size_t size, Byte * value) const;

		/// Helper to read values of specific type
		template <typename ObjectT>
		std::size_t read (std::size_t offset, ObjectT & value) const
		{
			read(offset, sizeof(ObjectT), (Byte *)&value);

			return sizeof(ObjectT);
		}

		template <typename ObjectT>
		std::size_t read (std::size_t offset, ObjectT & value, Endian src_type, Endian dst_type) const
		{
			std::size_t cnt = read(offset, value);
			endian_decode(value, src_type, dst_type);
			return cnt;
		}

		template <typename ObjectT>
		std::size_t read (std::size_t offset, ObjectT & value, Endian src_type) const
		{
			return read(offset, value, src_type, HOST_ENDIAN);
		}

		/// Access data at a particular location. Not range checked.
		const Byte & operator[] (std::size_t index) const;

		/// Returns true if size() == 0, otherwise false.
		bool empty () const { return size() == 0; };

		/// Returns the length of data stored in the buffer.
		virtual std::size_t size () const = 0;

		/// Returns the address of the first byte in the buffer.
		virtual const Byte * begin () const = 0;

		/// Returns the address of the last byte + 1 in the buffer.
		const Byte * end () const;

		/// Tests whether the data in the buffers is equivalent.
		bool operator== (const Buffer & other) const;

		/// Tests whether the data in the buffers is different.
		bool operator!= (const Buffer & other) const;

		/// Dump the buffer as hex to the given stream.
		void hexdump (std::ostream &) const;

		/// Basic data checksum
		uint32_t checksum () const;

		/// Write the contents of the buffer to the specified file path.
		void write_to_file (const std::string &) const;
		
		/// Write the contents of the buffer to the specified file descriptor.
		void write_to_stream (FileDescriptor output) const;
	};
	
	std::ostream & operator<< (std::ostream & out, const Buffer & buffer);
}
