//
//  MappedBuffer.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "MappedBuffer.hpp"

namespace Buffers
{
	MappedBuffer::MappedBuffer(const File & file, void * address, std::size_t length, int protection, int flags, off_t offset) : _length(length)
	{
		_data = mmap(address, length, protection, flags, file.descriptor(), offset);
		
		if (_data == MAP_FAILED)
			throw std::system_error(errno, std::system_category(), "mmap");
	}
	
	MappedBuffer::~MappedBuffer()
	{
		if (munmap(_data, _length) == -1)
			throw std::system_error(errno, std::system_category(), "munmap");
	}
	
	void MappedBuffer::advise(int advice)
	{
		if (madvise(_data, _length, advice) == -1)
			throw std::system_error(errno, std::system_category(), "madvise");
	}
}
