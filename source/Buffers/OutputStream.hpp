//
//  OutputStream.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "ResizableBuffer.hpp"

#include <iostream>

namespace Buffers
{
	// Provides std::istream interface to a buffer.
	class OutputStream : public std::ostream, private std::streambuf
	{
	public:
		OutputStream(ResizableBuffer & buffer);
		virtual ~OutputStream();
		
		OutputStream(const OutputStream &) = delete;
		OutputStream &operator= (const OutputStream &) = delete;
		
	protected:
		using std::streambuf::int_type;
		using std::streambuf::char_type;
		
		virtual int_type overflow(int_type ch);
		
	private:
		ResizableBuffer & _buffer;
	};
}
