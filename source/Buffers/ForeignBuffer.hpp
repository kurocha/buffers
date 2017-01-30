//
//  ForeignBuffer.hpp
//  File file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 30/1/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

namespace Buffers
{
	/// This buffer provides an easy way to wrap an existing free function. For example, TurboJPEG requires the use of tjFree on it's buffers, so you'd instantiate this buffer `new ForeignBuffer<Byte, jFree>(data_from_turbo_jpeg, size)`. The data type of the buffer is provided explicitly as some libraries use `unsigned char *` and others use `void`. When the buffer is deleted, the free function would be invoked to release the data.
	template <typename DataT, void(*free_function)(DataT *)>
	class ForeignBuffer : public Buffers::Buffer
	{
	public:
		ForeignBuffer(DataT * data, std::size_t size) : _data(data), _size(size) {
		}
		
		virtual ~ForeignBuffer() {
			free_function(_data);
		}
		
		/// Returns the length of data stored in the buffer.
		virtual std::size_t size () const { return _size; }

		/// Returns the address of the first byte in the buffer.
		virtual const Byte * begin () const { return static_cast<const Byte *>(_data); }
		
	private:
		DataT * _data = nullptr;
		std::size_t _size = 0;
	};
}
