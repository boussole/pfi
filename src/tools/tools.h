/*
 * \file    tools.h
 * \brief  
 * \details
 * \author  conquistador
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <common/common.h>

namespace conq_tools {

class Endian {
	/*************************
	 * \brief Invert value
	 *************************/
	static std :: uint32_t invert(void * v, std :: size_t len)
	{
		uint32_t value = 0;

		for (std :: size_t pos = 0; pos < len; ++pos) {
			std :: uint8_t byte = static_cast<std :: uint8_t *>(v)[pos];
			value |= byte << ((len - 1 - pos) * 8);
		}

		return value;
	}

public:
	enum class Type {
		LittleEndian,
		BigEndian
	};
	/*************************
	 * \brief htonl
	 *************************/
	static std :: uint32_t
	htonl(std :: uint32_t v)
	{ return invert(&v, 4); }

	/*************************
	 * \brief htons
	 *************************/
	static std :: uint16_t
	htons(std :: uint16_t v)
	{ return invert(&v, 2); }

	/**************************
	 * \brief ntohl
	 *************************/
	static std :: uint32_t
	ntohl(std :: uint32_t v)
	{ return invert(&v, 4); }

	/**************************
	 * \brief nhohs
	 *************************/
	static std :: uint16_t
	ntohs(std :: uint16_t v)
	{ return invert(&v, 2); }

	/*************************
	 * \brief Check endian of platform
	 *************************/
	static Type
	checkEndian()
	{
		std :: uint16_t val = 0xAABB;
		std :: uint8_t * ptr = static_cast<std :: uint8_t *>(static_cast<void *>(&val));
		return (ptr[0] == 0xBB) ? Type :: LittleEndian : Type :: BigEndian;
	}
};

} /* namespace conq_tools */

#endif /* TOOLS_H_ */
