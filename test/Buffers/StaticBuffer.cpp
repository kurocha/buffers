//
//  Test.StaticBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/StaticBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite StaticBufferTestSuite {
		"Buffers::StaticBuffer",
		
		{"it can be constructed from static c-string",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer buffer("Bobby");
				
				examiner << "Correct data size including null terminator." << std::endl;
				examiner.expect(buffer.size()) == 6;

				uint8_t value;
				buffer.read(2, value);

				examiner << "Read correct value from buffer." << std::endl;
				examiner.expect(value) == 'b';
			}
		},
	};
}
