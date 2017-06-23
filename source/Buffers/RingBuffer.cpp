//
//  RingBuffer.cpp
//  File file is part of the "Dream" project and released under the MIT License.
//
//  Created by Samuel Williams on 23/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "RingBuffer.hpp"

#include <algorithm>
#include <stdexcept>
#include <system_error>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

namespace Buffers
{
	RingBuffer::RingBuffer(MutableBuffer & storage) : _storage(storage)
	{
	}
	
	RingBuffer::~RingBuffer()
	{
	}
	
	std::size_t RingBuffer::total_size () const
	{
		return _size;
	}

	std::size_t RingBuffer::size () const
	{
		auto remainder = _storage.size() - _offset;
		
		return std::min(remainder, _size);
	}
	
	void RingBuffer::consume(std::size_t amount)
	{
		if (amount > _size) throw std::out_of_range("consuming more than available");
		
		// We do it this way to avoid any kind of overflow.
		auto remainder = _storage.size() - _offset;
		if (amount < remainder) {
			_offset += amount;
		} else {
			_offset = amount - remainder;
		}
		
		_size -= amount;
		
		// Reset the offset back to 0 if we consumed all data.
		if (_size == 0) {
			_offset = 0;
		}
	}
	
	bool RingBuffer::contiguous() const
	{
		// The RHS s the biggest offset which can possibly be contiguous.
		// Buffer size: 20, size: 8, offset <= 12 (base 0)
		// We do it this way to avoid any kind of buffer overflow.
		return _offset <= _storage.size() - _size;
	}
	
	Byte * RingBuffer::free_begin()
	{
		auto begin = this->end();
		
		if (begin == _storage.end())
			return _storage.begin();
		
		return begin;
	}
	
	Byte * RingBuffer::free_end()
	{
		auto end = this->begin();
		
		if (end == _storage.begin())
			return _storage.end();
		
		return end;
	}
	
	std::size_t RingBuffer::read_from(FileDescriptor file_descriptor)
	{
		// There are at most two discrete segments to read into.
		// [ * ] indicates used area.
		// < - > indicates free area (where we want to place data from read).
		
		// Here are the cases with no free space:
		// [ * * * * * * * * * * * * * * ] (0)
		// * * ] [ * * * * * * * * * * * * (1)
		
		// Here are all cases with one segment:
		// < - - - - - - - - - - - - - - > (2)
		// [ * * * ] < - - - - - - - - - > (3)
		// < - - - - - - - - - > [ * * * ] (4)
		// * * ] < - - - - - - - - - > [ * (5)
		
		// Here are all cases with two segments:
		// < - > [ * * * ] < - - - - - - > (6)
		
		// No free space to read into (case 0, 1).
		if (_size == _storage.size()) return 0;
		
		// We need to handle several cases here, as efficiently as possible.
		struct iovec iov[2];
		int count = 0;
		
		auto begin = this->free_begin();
		auto end = this->free_end();
		
		if (begin < end) {
			// Handle cases (2, 3, 4, 5)
			iov[0].iov_base = begin;
			iov[0].iov_len = end - begin;
			count = 1;
		} else {
			// Handle cases (6)
			iov[0].iov_base = begin;
			iov[0].iov_len = _storage.end() - begin;
			iov[1].iov_base = _storage.begin();
			iov[1].iov_len = end - _storage.begin();
			count = 2;
		}
		
		auto result = ::readv(file_descriptor, iov, count);
		
		if (result >= 0) {
			_size += result;
			
			return result;
		} else {
			if (errno == EAGAIN || errno == EINTR) {
				return 0;
			}
			
			throw std::system_error(errno, std::generic_category(), "readv");
		}
	}
	
	std::size_t RingBuffer::write_to(FileDescriptor file_descriptor)
	{
		// There are at most two discrete segments to write from.
		// [ * ] indicates used area (data we want to write).
		// < - > indicates free area.
		
		// Here are the cases with empty buffer:
		// < - - - - - - - - - - - - - - > (0)
		
		// Here are all cases with one segment:
		// [ * * * * * * * * * * * * * * ] (1)
		// [ * * * ] < - - - - - - - - - > (2)
		// < - - - - - - - - - > [ * * * ] (3)
		// < - > [ * * * ] < - - - - - - > (4)
		
		// Here are all cases with two segments:
		// * * ] < - - - - - - - - - > [ * (5)
		// * * ] [ * * * * * * * * * * * * (6)
		
		// Nothing No free space to read into (case 0, 1).
		if (_size == 0) return 0;
		
		// We need to handle several cases here, as efficiently as possible.
		struct iovec iov[2];
		int count = 0;
		
		auto begin = this->begin();
		auto end = this->end();
		
		if (begin < end) {
			// Handle cases (1, 2, 3, 4)
			iov[0].iov_base = begin;
			iov[0].iov_len = end - begin;
			count = 1;
		} else {
			// Handle cases (5)
			iov[0].iov_base = begin;
			iov[0].iov_len = _storage.end() - begin;
			iov[1].iov_base = _storage.begin();
			iov[1].iov_len = end - _storage.begin();
			count = 2;
		}
		
		auto result = ::writev(file_descriptor, iov, count);
		
		if (result >= 0) {
			_size -= result;
			
			return result;
		} else {
			if (errno == EAGAIN || errno == EINTR) {
				return 0;
			}
			
			throw std::system_error(errno, std::generic_category(), "writev");
		}
	}
}
