//
//  BufferStream.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

#include <iostream>

namespace Buffers
{
	class ByteStreamBuffer : public std::streambuf
	{
	public:
		ByteStreamBuffer(const Byte * begin, const Byte * end);

		ByteStreamBuffer(const ByteStreamBuffer &) = delete;
		ByteStreamBuffer &operator= (const ByteStreamBuffer &) = delete;

	protected:
		virtual int_type underflow();
		virtual int_type uflow();
		virtual int_type pbackfail(int_type ch);
		virtual std::streamsize showmanyc();

	private:
		const Byte * const _begin;
		const Byte * const _end;
		const Byte * _current;
	};

	/// Provides an istream interface to reading data from a buffer. This can be used to provide a buffer to a stream processing function.
	class BufferStream : public ByteStreamBuffer, public std::istream
	{
	public:
		BufferStream(const Buffer & buffer);
		virtual ~BufferStream();
		
	private:
		
	};
}
