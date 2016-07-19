//
//  BufferStream.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "BufferStream.hpp"

#include <cassert>

namespace Buffers
{
	// Explaination of how this fits together: http://www.mr-edd.co.uk/blog/beginners_guide_streambuf

	ByteStreamBuffer::ByteStreamBuffer(const Byte * begin, const Byte * end) : _begin(begin), _end(end), _current(_begin)
	{
		assert(_begin <= _end);
	}

	ByteStreamBuffer::int_type ByteStreamBuffer::underflow()
	{
		if (_current == _end)
			return traits_type::eof();

		return traits_type::to_int_type(*_current);
	}

	ByteStreamBuffer::int_type ByteStreamBuffer::uflow()
	{
		if (_current == _end)
			return traits_type::eof();

		return traits_type::to_int_type(*_current++);
	}

	ByteStreamBuffer::int_type ByteStreamBuffer::pbackfail(int_type ch)
	{
		if (_current == _begin || (ch != traits_type::eof() && ch != _current[-1]))
			return traits_type::eof();

		return traits_type::to_int_type(*--_current);
	}

	std::streamsize ByteStreamBuffer::showmanyc()
	{
		assert(_current <= _end);

		return _end - _current;
	}

	BufferStream::BufferStream(const Buffer & buffer) : ByteStreamBuffer(buffer.begin(), buffer.end()), std::istream(this)
	{
	}
	
	BufferStream::~BufferStream()
	{
	}
}
