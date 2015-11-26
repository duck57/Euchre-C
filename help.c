//
//  help.c
//  Euchre
//
//  Created by Chris J.M. on 11/19/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "help.h"

void h_defaults() {
	printf("\tThis is help about the defaults\n");
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
	printf("\tEnter a name for the player in %s position.\n", posName);
}

void h_AI_levels() {
	printf("\tAI levels:\n0 [human], 1, or 2\n");
	//printf("Negative numbers for debugging only.\n");
}

void h_trump() {
	printf("\tTrump index values:\n");
	printf("\t\t0: LoNo\n");
	printf("\t\t1: Clubs\n");
	printf("\t\t2: Diamonds\n");
	printf("\t\t3: Spades\n");
	printf("\t\t4: Hearts\n");
	printf("\t\t5: HiNo\n");
}

void h_betting() {
	printf("\tEnter the number of tricks you think you and your partner can make this hand.\n");
	printf("\tEarning more tricks than your bet adds the number of tricks you took to your score plus a two point bonus.\n");
	printf("\tFailing to beat your bet means your bet is subtracted from your team's score.\n");
	printf("\tTo call a loner or shooter, enter 24.\n");
	//printf("\tEnter -1 to place a random bet or -2 to place a computer-generated bet.");
}