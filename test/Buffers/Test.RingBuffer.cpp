//
//  Test.StaticBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/DynamicBuffer.hpp>
#include <Buffers/File.hpp>
#include <Buffers/RingBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite RingBufferTestSuite {
		"Buffers::RingBuffer",
		
		{"it can read data from a file",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer storage(1024);
				File random("/dev/random");
				
				RingBuffer ring_buffer(storage);
				ring_buffer.read_from(random.descriptor());
				
				examiner << "Filled the ring buffer with data from the file." << std::endl;
				examiner.expect(ring_buffer.size()) == 1024;
			}
		},
		
		{"it can read data from a file in chunks",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer storage(1024);
				File random("/dev/random");
				
				RingBuffer ring_buffer(storage);
				ring_buffer.read_from(random.descriptor());
				
				ring_buffer.consume(100);
				examiner.expect(ring_buffer.read_from(random.descriptor())) == 100;
				
				examiner << "Filled the ring buffer with data from the file." << std::endl;
				examiner.expect(ring_buffer.size()) == 924;
				examiner.expect(ring_buffer.total_size()) == 1024;
			}
		},
	};
}
