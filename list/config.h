#ifndef CONFIG_H
#define CONFIG_H

#include "alloc.h"

#define __NODE_ALLOCATOR_THREADS 0
#ifdef __USE_MALLOC
typedef tt::__malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;
#else
typedef tt::__default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
#endif

#endif

