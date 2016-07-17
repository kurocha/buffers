//
//  BufferStream.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "BufferStream.hpp"

namespace Buffers
{
	BufferStream::BufferStream(const Buffer & buffer)
	{
		std::streambuf::setg(buffer.begin(), buffer.begin(), buffer.end());
	}
	
	BufferStream::~BufferStream()
	{
	}
}
