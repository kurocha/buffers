//
//  DynamicBuffer.cpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 17/7/2016.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#include "DynamicBuffer.hpp"

namespace Buffers
{
	DynamicBuffer::DynamicBuffer()
	{
	}
	
	DynamicBuffer::DynamicBuffer(const Buffer & buffer)
	{
		this->assign(buffer);
	}
	
	DynamicBuffer & DynamicBuffer::operator=(const Buffer & buffer)
	{
		this->resize(0);
		
		this->assign(buffer);
		
		return *this;
	}
	
	DynamicBuffer::~DynamicBuffer()
	{
	}
}
