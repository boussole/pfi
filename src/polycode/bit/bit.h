/**
 * \file    bit.h
 * \brief   Utilities for bit operations
 * \details Here you can find only naive solutions, for fast solution see http://graphics.stanford.edu/~seander/bithacks.html
 * \author  boussole
 */

#ifndef BIT_H_
#define BIT_H_

#include <limits.h>
#include <common/common.h>

namespace conq_bit {

/**
 * \brief Return size of type in bits
 */
#define BITS_NUM(type) (CHAR_BIT * sizeof(type))

/**
 * \brief Print input value and bin representation
 * \tparam T Type of input value
 * \param[in] val Input value
 */
template <typename T>
static inline
void show_bin(T val)
{
	std :: cout << "val = " << val << ";\tbin = ";
	const uint32_t mask = 1;
	for (int pos = BITS_NUM(T) - 1; pos >= 0; pos--) {
		std :: cout << ((val & (mask << pos)) >> pos);
		if (pos && (pos % CHAR_BIT) == 0) {
			std :: cout << " ";
		}
	}

	std :: cout << ";" << std :: endl;
}

/**
 * \brief Replace neighbor bits
 *
 * Replace bits in odd position with not odd
 * \tparam T Type of input value
 * \param[in,out] val Value for changing
 */
template <typename T>
static inline
void replace_neighbor(T & val)
{
	T mask = 1, new_val = 0;

	for (std :: size_t pos = 0; pos < BITS_NUM(T); pos += 2) {
		new_val |= (val & (mask << (pos + 1))) >> 1;
		new_val |= (val & (mask << pos)) << 1;
	}

	val = new_val;
}

/**
 * \brief Sum of 1 bits (bit == 1)
 *
 * Analyze all bits in digit and return sum of 1 bits
 * (i.e 10(dec) = 1010(bin); result == 2).
 * \tparam T Type of input value
 * \param[in] val Input value
 * \return number of bits with value of 1
 * \note   Slow!!! (see wiki)
 */
template <typename T>
static inline
unsigned int count_setup_bits(T val)
{
	unsigned int num = 0;

	T mask = 1;
	for (std :: size_t pos = 0; pos < BITS_NUM(T); pos++) {
		if (val & (mask << pos)) {
			num++;
		}
	}

	return num;
}



/**
 * \brief Round to the nearest pow of 2
 * \return Pow of round OR -1
 */
static inline
int roundPow2(unsigned long & val)
{
	static const std :: size_t bits = sizeof(val) * CHAR_BIT;
	static const unsigned long highest_bit = ((unsigned long)1 << (bits - 1));

	if (val >= highest_bit) {
		return -1;
	}

	unsigned long h = highest_bit, prev_h = highest_bit;
	int pow = bits;

	while (h > val) {
		prev_h = h;
		h >>= 1;
		pow--;
	}

	val = prev_h;

	return pow;
}

} /** namespace conq_bit {*/

#endif /* BIT_H_ */
