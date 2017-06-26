//
//  InputStream.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "InputStream.hpp"

#include <cassert>

namespace Buffers
{
	// Explaination of how this fits together: http://www.mr-edd.co.uk/blog/beginners_guide_streambuf
	InputStream::InputStream(const Buffer & buffer) : std::istream(this), _buffer(buffer)
	{
	}
	
	InputStream::~InputStream()
	{
	}

	InputStream::int_type InputStream::underflow()
	{
		if (_offset == _buffer.size())
			return traits_type::eof();

		return traits_type::to_int_type(_buffer[_offset]);
	}

	InputStream::int_type InputStream::uflow()
	{
		if (_offset == _buffer.size())
			return traits_type::eof();

		return traits_type::to_int_type(_buffer[_offset++]);
	}

	InputStream::int_type InputStream::pbackfail(int_type ch)
	{
		if (_offset == 0 || (ch != traits_type::eof() && ch != _buffer[_offset - 1]))
			return traits_type::eof();

		return traits_type::to_int_type(_buffer[--_offset]);
	}

	std::streamsize InputStream::showmanyc()
	{
		assert(_offset <= _buffer.size());

		return _buffer.size() - _offset;
	}

}
