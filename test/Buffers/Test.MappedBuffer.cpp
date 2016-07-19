//
//  Test.MappedBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/StaticBuffer.hpp>
#include <Buffers/DynamicBuffer.hpp>
#include <Buffers/MappedBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite MappedBufferTestSuite {
		"Buffers::MappedBuffer",
		
		{"it can map a file into memory",
			[](UnitTest::Examiner & examiner) {
				std::string test_path = "/bin/bash";
				
				File test_file(test_path);
				MappedBuffer buffer(test_file, 1024);
				
				examiner.expect(buffer.size()) == 1024;
			}
		},
		
		{"it can write to memory mapped file",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer sample_data("The quick brown fox jumped over the lazy dog.");
				
				std::string test_path = "buffer.bin";
				
				DynamicBuffer test_data(sample_data.size());
				test_data.assign(sample_data);
				
				{
					File test_file(test_path, O_CREAT|O_TRUNC|O_RDWR);
					test_file.write(test_data);
				}
				
				{
					File test_file(test_path, O_RDONLY);
					
					examiner << "The test file has the correct size." << std::endl;
					examiner.expect(test_file.size()) == sample_data.size();
					
					test_file.read([&](Buffer & buffer){
						examiner << "The test file was written to and read correctly." << std::endl;
						examiner.expect(buffer) == test_data;
					});
				}
			}
		}
	};
}
