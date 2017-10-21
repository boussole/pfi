/**
 * \file    memory.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <cstddef>

namespace conq_mem {

/**
 * \brief Allocate with alignment
 */
void * AllocAlign(size_t size, size_t align);

/**
 * \brief Free alignment memory
 */
void FreeAlign(void * ptr);

} /* namespace conq_mem */

#endif /* MEMORY_H_ */
