//
//  File.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Buffer.hpp"

#include <string>
#include <sys/types.h>
#include <fcntl.h>

namespace Buffers
{
	// Opens a file for reading or writing.
	class File {
		FileDescriptor _descriptor;
		
	public:
		File(const std::string & path, int flags = O_RDONLY, std::uint16_t mode = 0644);
		~File();
		
		File(const File & other) = delete;
		File & operator=(const File &) = delete;
		
		std::size_t size() const;
		
		/// Destructively allocate space on disk for the given data size.
		void allocate(std::size_t size);
		
		FileDescriptor descriptor() const { return _descriptor; }
		
		/// Write the entire buffer to the file.
		void write(const Buffer & buffer);
		
		/// Read the file in it's entirety and yield to the block with the buffer.
		template <typename BlockT>
		void read(BlockT block);
	};
}
