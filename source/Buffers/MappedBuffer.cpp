//
//  MappedBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "MappedBuffer.hpp"

#include <system_error>

namespace Buffers
{
	MappedBuffer::MappedBuffer(const File & file, std::size_t length, int protection, int flags, off_t offset, void * address) : _length(length)
	{
		auto result = mmap(address, length, protection, flags, file.descriptor(), offset);
		
		if (result == MAP_FAILED)
			throw std::system_error(errno, std::system_category(), "mmap");

		_data = static_cast<Byte*>(result);
	}
	
	MappedBuffer::~MappedBuffer()
	{
		if (munmap(_data, _length) == -1)
			perror(__PRETTY_FUNCTION__);
	}
	
	void MappedBuffer::advise(int advice)
	{
		if (madvise(_data, _length, advice) == -1)
			throw std::system_error(errno, std::system_category(), "madvise");
	}
}
