//
//  Endian.hpp
//  This file is part of the "Buffers" project and released under the MIT License.
//
//  Created by Samuel Williams on 29/9/2006.
//  Copyright, 2016, by Samuel Williams. All rights reserved.
//

#pragma once

#include <cstddef>

namespace Buffers
{
	enum class Endian {
		BIG,
		LITTLE
	};

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	#define __LITTLE_ENDIAN__
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	#define __BIG_ENDIAN__
#endif

#if defined(__LITTLE_ENDIAN__) || defined(i386)
	constexpr Endian HOST_ENDIAN = Endian::LITTLE;
#elif defined(__BIG_ENDIAN__) || defined(ppc)
	constexpr Endian HOST_ENDIAN = Endian::BIG;
#endif
	
	/// Network order is big endian. Use this if you need to write something that deals specifically with network order.
	constexpr Endian NETWORK_ENDIAN = Endian::BIG;
	
	/// Decode a value in-place.
	/// @code
	/// uint32_t val = read_int(...);
	/// endian_decode(val, library_endian(), host_endian());
	/// @endcode
	template <typename BaseT>
	inline void endian_decode (BaseT & value, Endian src_type, Endian dst_type)
	{
		if (src_type != dst_type) {
			BaseT copy;
			order_copy(value, copy, src_type, dst_type);
			value = copy;
		}
	}

	// This interface can be used when reading data directly from memory.
	inline void order_copy (const unsigned char * src, unsigned char * dst, std::size_t len, Endian src_type, Endian dst_type)
	{
		if (src_type != dst_type) {
			dst += len - 1;
			for (std::size_t i = 0; i < len; i++)
				*(dst--) = *(src++);
		} else {
			for (std::size_t i = 0; i < len; i++)
				*(dst++) = *(src++);
		}
	}

	template <typename BaseT>
	void order_copy (const BaseT & _src, BaseT & _dst, Endian src_type, Endian dst_type)
	{
		const unsigned char * src = (const unsigned char *) &_src;
		unsigned char * dst = (unsigned char *) &_dst;

		order_copy(src, dst, sizeof(BaseT), src_type, dst_type);
	}

	template <typename BaseT>
	inline BaseT order_read (const BaseT & _src, Endian src_type, Endian dst_type)
	{
		BaseT r;
		order_copy(_src, r, src_type, dst_type);
		return r;
	}

	template <typename BaseT>
	inline void order_write (const BaseT & val, BaseT & dst, Endian src_type, Endian dst_type)
	{
		// for the time being this is the same as OrderRead
		order_copy(val, dst, src_type, dst_type);
	}
	
	/**
		A simple primative type wrapper that allows simple access to endian-correct value.

		Writing to the value using operator= will convert the value into the specified endian. Reading is done using the implicit cast operator, and will also cast the variable into the specified endian.

			template <Endian store_t>
			struct OrderedTestStruct {
				Ordered<uint32_t, store_t> value;
			};
		*/
	template <typename _BaseT, Endian MEMORY_ENDIAN = NETWORK_ENDIAN>
	class Ordered {
	public:
		typedef _BaseT BaseT;
		BaseT base;

		/// Implicit cast into the specified type.
		/// Will convert the internal value to host order.
		inline operator BaseT () const
		{
			return order_read(base, MEMORY_ENDIAN, HOST_ENDIAN);
		}

		/// Implicit cast into the specified type.
		/// Will convert the external value to the specified order
		inline const BaseT & operator= (const BaseT & value)
		{
			order_write(value, base, HOST_ENDIAN, MEMORY_ENDIAN);
			
			return value;
		}
	};

	template <typename BaseT, Endian MEMORY_ENDIAN, typename OtherT>
	bool operator== (const Ordered<BaseT, MEMORY_ENDIAN> & ordered, const OtherT & other)
	{
		return BaseT(ordered) == other;
	}

	template <typename BaseT, Endian MEMORY_ENDIAN, typename OtherT>
	bool operator!= (const Ordered<BaseT, MEMORY_ENDIAN> & ordered, const OtherT & other)
	{
		return BaseT(ordered) != other;
	}
}
