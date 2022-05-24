//
//  Test.InputStream.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 26/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/StaticBuffer.hpp>
#include <Buffers/InputStream.hpp>

namespace Buffers
{
	UnitTest::Suite InputStreamTestSuite {
		"Buffers::InputStream",
		
		{"it should have some real tests",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer buffer("Hello 123");
				InputStream stream(buffer);
				
				std::string string;
				stream >> string;
				examiner.expect(string) == "Hello";
				
				int number;
				stream >> number;
				examiner.expect(number) == 123;
			}
		},
	};
}
