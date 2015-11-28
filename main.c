//
//  main.c
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include <stdio.h>
#include <string.h>
#include "euchre.h"

int main(int argc, const char * argv[]) {
	int cont = 1;
	while (cont) {
		if (cont == 1)
			init_euchre(); // set player names and AI levels
		play_euchre();
		cont = repeat();
		if (cont)
			reset_euchre(); // reset scores and such
	}
    return 0;
}