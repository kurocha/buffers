//
//  Test.PackedBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/MappedBuffer.hpp>
#include <Buffers/PackedBuffer.hpp>
#include <Buffers/StaticBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite PackedBufferTestSuite {
		"Buffers::PackedBuffer",
		
		{"construct from string",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer sample_buffer("You might not think that programmers are artists, but programming is an extremely creative profession. It's logic based creativity.");

				PackedBuffer * buffer = PackedBuffer::allocate(sample_buffer.size());
				examiner << "Buffer was created successfully." << std::endl;
				examiner.expect(buffer) != nullptr;
				
				examiner << "Buffer has correct size." << std::endl;
				examiner.expect(buffer->size()) == sample_buffer.size();

				buffer->assign(sample_buffer);

				examiner << "Data is correct." << std::endl;
				examiner.expect(*buffer) == sample_buffer;
			}
		},
		
		{"reading and writing to file",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer sample_data("When the only tool you have is a hammer, you tend to treat everything as if it were a nail.");
				
				std::string tmp_path = "buffer.txt";

				PackedBuffer * write_buffer = PackedBuffer::allocate(sample_data.size());
				write_buffer->assign(sample_data);
				write_buffer->write_to_file(tmp_path);
				
				File tmp_file(tmp_path, O_RDONLY);
				
				examiner << "File size is same as sample data size." << std::endl;
				examiner.expect(tmp_file.size()) == sample_data.size();
				
				MappedBuffer read_buffer(tmp_file, tmp_file.size());
				
				examiner << "Data is correct." << std::endl;
				examiner.expect(*write_buffer) == read_buffer;
			}
		}
	};
}
