//
//  RingBuffer.hpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 23/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "MutableBuffer.hpp"

namespace Buffers
{
	class RingBuffer : public MutableBuffer
	{
	public:
		RingBuffer(MutableBuffer & storage);
		virtual ~RingBuffer();
		
		/// The total data size in the ring buffer of all segments.
		std::size_t total_size () const;
		
		/// The contiguous length of the buffer.
		virtual std::size_t size() const;
		
		/// The start of the first contiguous segment.
		virtual Byte * begin() {return _storage.begin() + _offset;}
		virtual const Byte * begin() const {return _storage.begin() + _offset;}
		
		/// Increment the head of the buffer by the given amount.
		/// throw std::out_of_range if this would increment head past the tail.
		void consume(std::size_t amount);
		
		// Whether the ring buffer has one contiguous segment or has wrapped around.
		bool contiguous() const;
		
		std::size_t read_from(FileDescriptor file_descriptor);
		std::size_t write_to(FileDescriptor file_descriptor);
		
	private:
		Byte * free_begin();
		Byte * free_end();
		
		std::size_t _offset = 0, _size = 0;
		
		MutableBuffer & _storage;
	};
}
