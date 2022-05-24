//
//  Test.Buffer.cpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 22/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Buffers/StaticBuffer.hpp>
#include <Buffers/DynamicBuffer.hpp>

namespace Buffers
{
	UnitTest::Suite BufferTestSuite {
		"Buffers::Buffer",
		
		{"it can compare buffers of the same length",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer a("abc");
				StaticBuffer b("abd");
				
				examiner.expect(a) != b;
				examiner.expect(a.compare(b)) == -1;
				examiner.expect(a.compare(a)) == 0;
				examiner.expect(b.compare(a)) == 1;
			}
		},
		
		{"it can compare different buffers with the same value",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer a("abc");
				DynamicBuffer b(a); // Same data, but copied to a different memory address.
				
				examiner.expect(a) == b;
				examiner.expect(b) == a;
				examiner.expect(a.compare(b)) == 0;
				examiner.expect(b.compare(a)) == 0;
			}
		},
		
		{"it can compare buffers of different lenghts",
			[](UnitTest::Examiner & examiner) {
				StaticBuffer a("abc");
				StaticBuffer b("abcd");
				
				examiner.expect(a) != b;
				examiner.expect(a.compare(b)) == -1;
				examiner.expect(a.compare(a)) == 0;
				examiner.expect(b.compare(a)) == 1;
			}
		},
		
		{"it can compare empty buffer with non-empty buffer",
			[](auto examiner) {
				StaticBuffer a("How you look at it is pretty much how you'll see it.");
				DynamicBuffer b;
				
				examiner.expect(a) != b;
				examiner.expect(b) != a;
				
				examiner.expect(a.compare(b)) == 1;
				examiner.expect(b.compare(a)) == -1;
			}
		},
		
		{"it can compare empty buffers",
			[](UnitTest::Examiner & examiner) {
				DynamicBuffer a, b;
				
				examiner.expect(a) == b;
				examiner.expect(b) == a;
				
				examiner.expect(a.compare(b)) == 0;
				examiner.expect(b.compare(a)) == 0;
			}
		},
	};
}
