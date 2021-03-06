//
//  MappedBuffer.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "MutableBuffer.hpp"
#include "File.hpp"

#include <sys/mman.h>

namespace Buffers
{
	class MappedBuffer : public MutableBuffer
	{
	public:
		MappedBuffer(const File & file, std::size_t length, int protection = PROT_READ, int flags = MAP_SHARED, off_t offset = 0, void * address = 0);
		virtual ~MappedBuffer();
		
		void advise(int advice);
		
		virtual Byte * begin() { return _data; }
		virtual const Byte * begin() const { return _data; }
		
		virtual std::size_t size() const { return _length; }
		
	private:
		std::size_t _length = 0;
		Byte * _data = nullptr;
	};
	
	template <typename BlockT>
	void File::read(BlockT block)
	{
		MappedBuffer buffer(*this, size());
		
		block(buffer);
	}
}
