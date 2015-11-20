//
//  numberTest.c
//  Euchre
//
//  Created by Chris Matlak on 11/19/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "mathemagics.h"


void modtest(int players);


int main(int argc, const char * argv[]) {
	char test[420];
	printf("Enter a smallish number: ");
	scanf("%[^\n]%*c", test);
	if (is_valid_int(test))
		modtest(to_int(test));
	printf("\n%d\t%d\n",is_valid_int(test),to_int(test));
	printf("%d\t%g\n",is_valid_number(test),to_double(test));
	return 420;
}

void modtest(int players) {
	printf("Plus\nL ");
	for (int i=0; i<players; i++) {
		printf(" %d", i);
	}
	printf("\n -");
	for (int i=0; i<players; i++) {
		printf("- ");
	}
	for (int lead=0; lead<players; lead++) {
		printf("\n%d ",lead);
		for (int loc=0; loc<players; loc++) {
			printf(" %d",(lead+loc)%players);
		}
	}
	printf("\n\n");
	printf("Minus\nL ");
	for (int i=0; i<players; i++) {
		printf(" %d", i);
	}
	printf("\n -");
	for (int i=0; i<players; i++) {
		printf("- ");
	}
	for (int lead=0; lead<players; lead++) {
		printf("\n%d ",lead);
		for (int loc=0; loc<players; loc++) {
			printf(" %d",mod(lead-loc, players));
		}
	}
	printf("\n");
}