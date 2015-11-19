//
//  numberTest.c
//  Euchre
//
//  Created by Chris Matlak on 11/19/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>


int main(int argc, const char * argv[]) {
	printf("Plus\nL  0 1 2 3\n -- - - -\n");
	for (int lead=0; lead<4; lead++) {
		printf("%d  ",lead);
		for (int loc=0; loc<4; loc++) {
			printf("%d ",(lead+loc)%4);
		}
		printf("\n");
	}
	
	printf("\nlead-loc\nL  0 1 2 3\n -- - - -\n");
	for (int lead=0; lead<4; lead++) {
		printf("%d  ",lead);
		for (int loc=0; loc<4; loc++) {
			printf("%d ",(lead-loc)%4);
		}
		printf("\n");
	}
	
	printf("\nloc-lead\nL  0 1 2 3\n -- - - -\n");
	for (int lead=0; lead<4; lead++) {
		printf("%d  ",lead);
		for (int loc=0; loc<4; loc++) {
			printf("%d ",(loc-lead)%4);
		}
		printf("\n");
	}
	return 420;
}