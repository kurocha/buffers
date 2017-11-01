//
//  File.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "File.hpp"

#include "MappedBuffer.hpp"

// File and memory manipulation
#include <sys/fcntl.h>
#include <unistd.h>

#include <iostream>

#include <system_error>

namespace Buffers
{
	File::File(const std::string & path, int flags, mode_t mode)
	{
		_descriptor = open(path.c_str(), flags, mode);
		
		if (_descriptor == -1)
			throw std::system_error(errno, std::system_category(), "open");
	}
	
	File::~File()
	{
		if (_descriptor > 0) {
			// This is a bad situation to be in:
			if (close(_descriptor) == -1)
				throw std::system_error(errno, std::system_category(), "close");
		}
	}
	
	std::size_t File::size() const
	{
		auto current_offset = lseek(_descriptor, 0, SEEK_CUR);
		
		lseek(_descriptor, 0, SEEK_END);
		
		auto size = lseek(_descriptor, 0, SEEK_CUR);
		
		lseek(_descriptor, current_offset, SEEK_SET);
		
		return size;
	}
	
	void File::write(const Buffer & buffer)
	{
		auto required_size = buffer.size();
		
		allocate(required_size);
		
		MappedBuffer mapped_buffer(*this, required_size, PROT_WRITE);
		mapped_buffer.advise(MADV_SEQUENTIAL);
		
		mapped_buffer.assign(buffer);
	}
	
#ifdef __APPLE__
	static int posix_fallocate(int file_descriptor, off_t offset, off_t length)
	{
		fstore_t store = {F_ALLOCATECONTIG, F_PEOFPOSMODE, offset, length, 0};
		
		// Try to get a continous chunk of disk space
		int result = fcntl(file_descriptor, F_PREALLOCATE, &store);
		
		if (result == -1) {
			// OK, perhaps we are too fragmented, allocate non-continuous
			store.fst_flags = F_ALLOCATEALL;
			
			result = fcntl(file_descriptor, F_PREALLOCATE, &store);
			
			if (result == -1) {
				// APFS doens't seem to support F_PREALLOCATE and always returns EINVAL, so ignore it.
				if (errno != EINVAL) {
					return errno;
				}
			}
		}
	
		if (ftruncate(file_descriptor, length) == -1) {
			return errno;
		}
		
		return 0;
	}
#endif
	
	void File::allocate(std::size_t size) {
		// posix_fallocate doesn't set errno; it returns an errno.
		int result = posix_fallocate(_descriptor, 0, size);
		
		if (result != 0)
			throw std::system_error(result, std::system_category(), "posix_fallocate");
	}
}
