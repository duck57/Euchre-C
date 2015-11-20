//
//  menus.c
//  Euchre
//
//  Created by Chris Matlak on 11/18/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "menus.h"


void greet() {
	printf("Welcome to double-deck euchre!\n");
	printf("Enter ? or H at any time and relevant help will be displayed.\n\n");
}

void set_players() {
	char oneChar;
	init_players();
	while (oneChar=='\0') {
		printf("Enter through this prompt to use default players.\nAnything else to go into setup: ");
		scanf("%c",&oneChar);
		if (oneChar=='?' || oneChar=='h' || oneChar=='H') {
			h_defaults();
			oneChar='\0';
		} else if (oneChar=='\n') {
			default_players();
			return;
		}
		getchar();
	}
	printf("\n\nPlayer Setup~~\n\n");
	for (int i=0; i<4; i++) {
		setup_player(i);
	}
}

int help(char *chk) {
	return strcmp(chk, "H")==0 || strcmp(chk, "h")==0 || strcmp(chk, "?")==0;
}


// TODO: Work here!!!!
void setup_player(int playerNumber) {
	printf("Setup %s:\n",playerList[playerNumber].name);
	get_name(playerNumber);
}

void get_name(int playerNumber) {
	char *name = malloc(100*sizeof(char));
	while (!name) {
		printf("Name: ");
		scanf("%c", name);
		if (help(name)) {
			h_name(playerNumber);
			name='\0';
		} else if (strcmp(name, "\n")==0) {
			return;
		}
		getchar();
	}
}

void set_AI(int playerNumber) {
	char *in = NULL;
	int AIlevel = -600;
	while (AIlevel == -600) {
		printf("AI strength (0 [human], 1, or 2): ");
		scanf("%c", in);
		if (help(in)) {
			h_name(playerNumber);
			in='\0';
		} else if (strcmp(in, "\n")==0) {
			return;
		} else if (!is_valid_int(in)) {
			printf("\nEnter a number.\n");
		} else {
			AIlevel = to_int(in);
			AIlevel = AIlevel > -5 && AIlevel < 3 ? AIlevel : -600;
		}
		getchar();
	}
	playerList[playerNumber].AI = AIlevel;
}