//
//  InputStream.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

#include <iostream>

namespace Buffers
{
	// Provides std::istream interface to a buffer.
	class InputStream : public std::istream, private std::streambuf
	{
	public:
		InputStream(const Buffer & buffer);
		virtual ~InputStream();
		
		InputStream(const InputStream &) = delete;
		InputStream &operator= (const InputStream &) = delete;

	protected:
		using std::streambuf::traits_type;
		using std::streambuf::int_type;
		
		virtual int_type underflow();
		virtual int_type uflow();
		virtual int_type pbackfail(int_type ch);
		virtual std::streamsize showmanyc();

	private:
		const Buffer & _buffer;
		std::size_t _offset = 0;
	};
}
