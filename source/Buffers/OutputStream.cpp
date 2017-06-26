//
//  OutputStream.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "OutputStream.hpp"

namespace Buffers
{
	OutputStream::OutputStream(ResizableBuffer & buffer) : std::ostream(this), _buffer(buffer)
	{
	}
	
	OutputStream::~OutputStream()
	{
	}
	
	OutputStream::int_type OutputStream::overflow(int_type ch)
	{
		// Append a single character:
		_buffer.expand(1);
		_buffer[_buffer.size() - 1] = (char_type)ch;
		
		return ch;
	}
}
