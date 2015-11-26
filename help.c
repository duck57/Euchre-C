//
//  help.c
//  Euchre
//
//  Created by Chris J.M. on 11/19/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "help.h"

void h_defaults() {
	printf("This is help about the defaults\n");
}

void h_name(int pPos) {
	char *posName;
	switch (pPos) {
		case 0:
			posName = "East";
			break;
		case 1:
			posName = "South";
			break;
		case 2:
			posName = "West";
			break;
		case 3:
			posName = "North";
			break;
			
		default:
				break;
	}
	printf("Enter a name for the player in %s position.\n", posName);
}

void h_AI_levels() {
	printf("AI levels:\n0 [human], 1, or 2\nNegative numbers for debugging only.\n");
}