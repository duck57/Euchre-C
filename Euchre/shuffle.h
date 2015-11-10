//
//  shuffle.h
//  Euchre
//
//  Created by Chris Matlak on 3/28/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_shuffle_h
#define Euchre_shuffle_h

#include <time.h>
#include <stdlib.h>
#include <string.h>

static void shuffle(void *array, size_t n, size_t size);

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))
#define foo4random() (arc4random() % ((unsigned)RAND_MAX + 1))


#define print_type(count, stmt) \
do { \
printf("["); \
for (size_t i = 0; i < (count); ++i) { \
stmt; \
} \
printf("]\n"); \
} while (0)

#endif

/* arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
static inline void shuffle(void *array, size_t n, size_t size) {
	char tmp[size];
	char *arr = array;
	size_t stride = size * sizeof(char);
	
	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; ++i) {
			size_t rnd = (size_t) rand();
			size_t j = i + rnd / (RAND_MAX / (n - i) + 1);
			
			memcpy(tmp, arr + j * stride, size);
			memcpy(arr + j * stride, arr + i * stride, size);
			memcpy(arr + i * stride, tmp, size);
		}
	}
}