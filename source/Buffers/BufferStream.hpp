//
//  BufferStream.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include <iostream>

namespace Buffers
{
	/// Provides an istream interface to reading data from a buffer. This can be used to provide a buffer to a stream processing function.
	class BufferStream : public std::streambuf, public std::istream
	{
	public:
		BufferStream(const Buffer & buffer);
		virtual ~BufferStream();
		
	private:
		
	};
}
