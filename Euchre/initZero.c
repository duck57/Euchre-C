//
//  initZero.c
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "initZero.h"


void zero_players() {
	for (int i = 0; i < 4; i++) {
		playerList[i].AI = 0;
		playerList[i].name = "";
		playerList[i].tricks = 0;
		playerList[i].bet = 0;
	}
}

void init_players() {
	playerList[0].name = "EAST"; //Amanda
	playerList[0].AI = 1;
	playerList[1].name = "SOUTH"; //Chris
	playerList[1].AI = 1;
	playerList[2].name = "WEST"; //Ben
	playerList[2].AI = 1;
	playerList[3].name = "NORTH"; //Michelle
	playerList[3].AI = 1;
}

void default_players() {
	playerList[0].name = "Amanda"; //EAST
	playerList[0].AI = 2;
	playerList[1].name = "Chris"; //SOUTH
	playerList[1].AI = 0;
	playerList[2].name = "Ben"; //WEST
	playerList[2].AI = 2;
	playerList[3].name = "Michelle"; //NORTH
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