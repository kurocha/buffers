//
//  Test.DynamicBuffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 19/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/DynamicBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite DynamicBufferTestSuite {
		"Buffers::DynamicBuffer",
		
		{"it can construct buffers",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer a(100), b, c(100, true);

				examiner << "Size set by constructor";
				examiner.check(a.size() == 100);
				examiner << "Size set by constructor";
				examiner.check(b.size() == 0);
				examiner << "Size set by constructor";
				examiner.check(c.size() == 0);

				examiner << "Sized construtor is not empty";
				examiner.check(!a.empty());
				examiner << "Default construtor is empty";
				examiner.check(b.empty());
				examiner << "Reserved construtor is empty";
				examiner.check(c.empty());

				examiner << "Capacity >= size";
				examiner.check(a.capacity() >= a.size());
				examiner << "Capacity >= size";
				examiner.check(b.capacity() >= b.size());
				examiner << "Capacity as specified";
				examiner.expect(c.capacity()) == 100;
			}
		},
		
		{"it should expand to required capacity",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer a(100), b;
				
				a.reserve(200);
				examiner << "Reserved capacity for 200 bytes";
				examiner.expect(a.capacity()) == 200;

				b.reserve(400);
				examiner << "Reserved capacity for 400 bytes";
				examiner.expect(b.capacity()) == 400;

				a.resize(600);
				examiner << "Resized to specified size";
				examiner.expect(a.size()) == 600;
				examiner << "Capacity increased after size increase";
				examiner.expect(a.capacity()) >= 600;

				a.expand(100);
				examiner << "Expanded size by requested amount";
				examiner.expect(a.size()) == 700;
			}
		},
		
		{"it can append data",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer a;
				
				a.append(5, (const Byte *)"abcde");
				a.append(5, (const Byte *)"abcde");

				examiner << "Size is correct after appending 10 characters";
				examiner.expect(a.size()) == 10;
				
				examiner << "Character is correct";
				examiner.expect(a[1]) == 'b';
			}
		},
		
		{"it can clear buffers",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer a(10), b(10);
				
				a.clear();
				examiner << "Cleared buffer is empty";
				examiner.check(a.empty());

				examiner << "Buffers are different after being cleared";
				examiner.expect(a) != b;

				b.clear();
				examiner << "Cleared buffers are equivalent";
				examiner.expect(a) == b;
			}
		},
		
		{"it can assign data and resize",
			[](UnitTest::Examiner & examiner) {
				std::string sample_string = "Human resources are human first, and resources second.";
				
				DynamicBuffer a(100), b;

				std::size_t prev_capacity = a.capacity();
				a.resize(sample_string.size());
				a.assign(sample_string);

				// Performance check
				examiner << "Don't realloc if size is within capacity";
				examiner.expect(a.capacity()) == prev_capacity;

				b.resize(sample_string.size());
				b.assign(sample_string);

				examiner << "Data and size is the same";
				examiner.expect(a) == b;
			}
		},
	};
}



