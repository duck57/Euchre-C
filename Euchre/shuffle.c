//
//  shuffle.c
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include "shuffle.h"

/* arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
void shuffle(void *array, const size_t n, const size_t size) {
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

#define ONESEC	1000000
void h(const double time) {
	struct timeval tv;
	tv.tv_sec = (int)time;
	tv.tv_usec = (int)(time*ONESEC)%ONESEC;
	
	select(1, NULL, NULL, NULL, &tv);
}