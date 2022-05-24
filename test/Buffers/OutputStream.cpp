//
//  Test.OutputStream.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/DynamicBuffer.hpp>
#include <Buffers/OutputStream.hpp>

namespace Buffers
{
	UnitTest::Suite OutputStreamTestSuite {
		"Buffers::OutputStream",
		
		{"it should have some real tests",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer buffer;
				OutputStream stream(buffer);
				
				stream << "The meaning of life is: " << 42 << std::endl;
				
				examiner.expect(std::string(buffer.begin(), buffer.end())) == "The meaning of life is: 42\n";
			}
		},
	};
}
