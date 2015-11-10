//
//  shuffle.c
//  Euchre
//
//  Created by Chris Matlak on 3/28/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shuffle.h"

/* compile and run with
 * cc shuffle.c -o shuffle && ./shuffle */

void demo_shuffle();


struct cmplex {
    int foo;
    double bar;
};

void demo_shuffle() {
	srand48(time(NULL));
	
    int intarr[] = { 1, -5, 7, 3, 20, 2 };
    
    print_type(NELEMS(intarr), printf("%d,", intarr[i]));
    shuffle(intarr, NELEMS(intarr), sizeof(intarr[0]));
    print_type(NELEMS(intarr), printf("%d,", intarr[i]));
    
    struct cmplex cmparr[] = {
        { 1, 3.14 },
        { 5, 7.12 },
        { 9, 8.94 },
        { 20, 1.84 }
    };
    
    print_type(NELEMS(intarr), printf("{%d %f},", cmparr[i].foo, cmparr[i].bar));
    shuffle(cmparr, NELEMS(cmparr), sizeof(cmparr[0]));
    print_type(NELEMS(intarr), printf("{%d %f},", cmparr[i].foo, cmparr[i].bar));
    
}