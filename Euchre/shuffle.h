//
//  shuffle.h
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#ifndef Euchre_shuffle_h
#define Euchre_shuffle_h

#include <time.h>
#include <string.h>
#include <unistd.h>
#include "mathemagics.h"

void shuffle(void *array, size_t n, size_t size);
void h(double time);

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