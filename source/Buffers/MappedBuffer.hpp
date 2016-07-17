//
//  MappedBuffer.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "MutableBuffer.hpp"

#include <sys/mman.h>

namespace Buffers
{
	class MappedBuffer : public Buffer
	{
	public:
		MappedBuffer(const File & file, std::size_t length, void * address = 0, int protection = PROT_READ, int flags = MAP_SHARED, off_t offset = 0);
		virtual ~MappedBuffer();
		
		void advise(int advice);
		
		virtual Byte * begin() { return _data; }
		virtual const Byte * begin() const { return _data; }
		
		virtual std::size_t size() { return _length; }
		
	private:
		std::size_t _length;
		void * _data;
	};
}
