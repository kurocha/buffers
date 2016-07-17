//
//  File.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Buffers
{
	typedef int FileDescriptor;
	
	// Opens a file for reading or writing.
	class File {
		FileDescriptor _descriptor;
		
	public:
		File(const std::string & path, int flags, mode_t mode);
		~File();
		
		File(const File & other) = delete;
		File & operator=(const File &) = delete;
		
		/// Allocate space on disk for the given data size.
		void allocate(std::size_t size);
		
		FileDescriptor descriptor() const { return _descriptor; }
		
		void write(Buffer & buffer);
	};
}
