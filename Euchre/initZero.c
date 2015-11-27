//
//  initZero.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "initZero.h"


void zero_players() {
	for (int i = 0; i < 4; i++) {
		playerList[i].AI = 0;
		strcpy(playerList[i].name, "");
		playerList[i].tricks = 0;
		playerList[i].bet = 0;
	}
}

// If *only* these defaults are used (which shouldn't happen), it will be the normal AI with directional names
void init_players() {
	int defaultAI = 1;
	
	// Amanda
	strcpy(playerList[0].name, "EAST");
	playerList[0].AI = defaultAI;
	playerList[0].pos = 0;
	
	// Chris
	strcpy(playerList[1].name, "SOUTH");
	playerList[1].AI = defaultAI;
	playerList[1].pos = 1;
	
	// Ben
	strcpy(playerList[2].name, "WEST");
	playerList[2].AI = defaultAI;
	playerList[2].pos = 2;
	
	// Michelle
	strcpy(playerList[3].name, "NORTH");
	playerList[3].AI = defaultAI;
	playerList[3].pos = 3;
}

/*
 EAST & WEST are a top AI and the good AI
 NORTH & SOUTH are a top AI and a human
 Balance this as necessary
 */
void default_players() {
	// EAST
	strcpy(playerList[0].name, "Amanda");
	playerList[0].AI = 1;
	
	// SOUTH
	strcpy(playerList[1].name, "Chris");
	playerList[1].AI = 0;
	
	// WEST
	strcpy(playerList[2].name, "Ben");
	playerList[2].AI = 2;
	
	// NORTH
	strcpy(playerList[3].name, "Michelle");
	playerList[3].AI = 2;
}

void zero_trick() {
	for (int i=0; i<4; i++) {
		trick[i]=blank_card();
	}
}

void zero_discard() {
	for (int i=0; i<44; i++) {
		discard[i]=blank_card();
	}
}

void init_euchre() {
	sec = 1.0; // change me to speed up autoplay games
	greet();
	set_players();
}

void reset_euchre() {
	for (int i = 0; i < 4; i++) {
		playerList[i].tricks = 0;
		playerList[i].bet = 0;
	}
	zero_trick();
	zero_discard();
	betEW = 0;
	betNS = 0;
	scoreEW = 0;
	scoreNS = 0;
}