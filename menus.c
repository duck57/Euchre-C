//
//  menus.c
//  Euchre
//
//  Created by Chris J.M. on 11/18/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "menus.h"

void greet() {
	printf("Welcome to double-deck euchre!\n");
	printf("Enter ? or H at any time and relevant help will be displayed.\n\n");
	
	// have to be given a value somewhere
	UNINIT = -600;
	HELP = 30;
	NOTHING = 10;
	ENTERED = 40;
	OVER = 20;
	OUT = 2;
	ERROR = 7;
}

void set_players() {
	char oneChar[2];
	int stat = UNINIT;
	init_players();
	while (stat != 0) {
		stat = input("Enter through this prompt to use default players.\nAnything else to go into setup: ", oneChar, sizeof(oneChar));
		if (stat == 3) {
			h_defaults();
		} else if (stat == 1 || stat == 4) {
			printf("Using default players.\n\n\n\n");
			default_players();
			return;
		} else if (stat == 2) {
			//printf("Input too long, but that doesn't matter.\n");
			stat = 0;
		}
	}
	printf("\n\nPlayer Setup~~\n");
	for (int i=0; i<4; i++) {
		setup_player(i);
	}
	printf("\n\n\n");
}

int help(char *chk) {
	return strcmp(chk, "H")==0 || strcmp(chk, "h")==0 || strcmp(chk, "?")==0;
}


void setup_player(int playerNumber) {
	printf("\nSetup %s:\n", playerList[playerNumber].name);
	get_name(playerNumber);
	set_AI(playerNumber);
}

void get_name(int playerNumber) {
	char name[NAME_LENGTH];
	int stat = UNINIT;
	while (stat != 0) {
		stat = input("Name: ", name, sizeof(name));
		switch (stat) {
			case 0:
				break;
			case 1:
				printf("\tNull string not expected in normal operation; will use a default and continue.\n");
				return;
			case 2:
				printf("\tName will be truncated.\n");
				stat = 0; // but that's OK
			case 3:
				h_name(playerNumber);
				break;
			case 4:
				printf("\tUsing default name %s.\n", playerList[playerNumber].name);
				return;
				
			default:
				printf("\tSomething went seriously wrong here; will pretend everything is normal.\n");
				break;
		}
	}
	strcpy(playerList[playerNumber].name, name);
}

void set_AI(int playerNumber) {
	int AIlevel = UNINIT;
	while (AIlevel == UNINIT) {
		AIlevel = get_number_in_range("AI strength: ", -4, 2, 2);
		if (AIlevel == HELP * UNINIT)
			h_AI_levels();
		else if (AIlevel == ENTERED * UNINIT || AIlevel == NOTHING * UNINIT) {
			printf("\tDefaulting to a smart AI.\n");
			AIlevel = 2;
		}
		if (AIlevel < -4)
			AIlevel = UNINIT;
	}
	playerList[playerNumber].AI = AIlevel;
}

int get_number_in_range(char *prompt, int min, int max, int digits) {
	char numberIN[digits+1]; //the +1 is to handle the return button and negative numbers
	int stat = UNINIT;
	int numberOut = UNINIT;
	while (numberOut == UNINIT) { // can't use numberOut == UNINIT for some reason
		stat = input(prompt, numberIN, sizeof(numberIN));
		switch (stat) {
			case 0: // Some in the correct buffer size
				if (!is_valid_number(numberIN)) {
					printf("\tEnter a number.\n\t%s\t->\t%d\n", numberIN, to_int(numberIN));
				} else {
					numberOut = to_int(numberIN);
					if (numberOut < min || numberOut > max) {
						numberOut = 2 * UNINIT;
						printf("\tOut of range.\n");
					}
				}
				break;
			case 1: // No input
				printf("\tNull string not expected in normal operation; will use a default and continue.\n");
				return NOTHING * UNINIT;
				break;
			case 2: // Too large for buffer
				printf("\tMagnitude too great.\n");
				return OVER * UNINIT;
				break;
			case 3: // help request
				return HELP * UNINIT;
				break;
			case 4: // entering through and\or defaulting
				return ENTERED * UNINIT;
				break;
				
			default: // something's not right
				printf("\tSomething went seriously wrong here; will pretend everything is normal.\n");
				return ERROR * UNINIT;
				break;
		}
	}
	return numberOut;
}

//from Stack Overflow
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
int getLine (char *prmpt, char *buff, size_t sz) {
	int ch, extra;
	
	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf ("%s", prmpt);
		fflush (stdout);
	}
	if (fgets (buff, (int)sz, stdin) == NULL) // (int) to make the conversion explicit and play nice w/ compiler
		return NO_INPUT;
	
	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff)-1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}
	
	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff)-1] = '\0';
	return OK;
}

// Wraps the input function and the help
#define HELP	3
#define ENTER	4
int input(char *prompt, char *readBuff, size_t size) {
	int stat = getLine(prompt, readBuff, size);
	if (readBuff[0] == '\0')
		return ENTER;
	return help(readBuff) ? HELP : stat;
}