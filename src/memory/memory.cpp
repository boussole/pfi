/*
 * memory.cpp
 *
 *  Created on: 29.08.2014
 *      Author: user
 */

#include "memory.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

namespace conq_mem {

/**
 * \brief Get original addr
 */
static inline void * OrigPtrStorageFromAlign(void * dst)
{
	dst = (void *)((uintptr_t)dst - sizeof(void *));
	dst = (void *)((uintptr_t)dst - ((uintptr_t)dst % sizeof(void *)));

	return dst;
}

/**
 * \brief Allocate with alignment
 */
void * AllocAlign(size_t size, size_t align)
{
	if (align == 0) {
		align = 1;
	}

	void * orig = malloc(size + sizeof(void *) + align);

	if (!orig) {
		return NULL;
	}

	void * dst = (uint8_t *)orig + sizeof(void *);
	uintptr_t offset = (uintptr_t)dst % align;
	dst = (void *)((uintptr_t)dst + (align - offset));
	void * save_orig = OrigPtrStorageFromAlign(dst);
	*((void **)save_orig) = orig;
	assert(orig == *((void **)OrigPtrStorageFromAlign(dst)));
	assert(((uintptr_t)OrigPtrStorageFromAlign(dst) % sizeof(void *)) == 0);

	return dst;
}

/**
 * \brief Free alignment memory
 */
void FreeAlign(void * ptr)
{
	void * orig = *((void **)OrigPtrStorageFromAlign(ptr));
	free(orig);
}

} /* namespace conq_mem */
