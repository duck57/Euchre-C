//
//  table.h
//  Euchre
//
//  Created by Chris Matlak on 11/18/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#ifndef table_h
#define table_h

#include "card.h"

typedef struct player_t {
	card_t hand[12];
	char *name; // Player name
	int AI; // AI strength of 0 == human player, see ai.c for more details
	int tricks; // how many tricks you took
	int bet; // your bet
	int bidList[7]; // used for AI bidding, see ai.c for more details
} player_t;

// Some shared assets
player_t playerList[4];
card_t euchreDeck[48];
card_t trick[4];
card_t discard[48]; // used for advanced AI
int trickNumber;

/*	Common-knowledge variables are declared here to prevent excessive parameterization
	If it's not intended to me at all malleable, it's declared in euchre.c */
int scoreNS, scoreEW;
int betNS, betEW;
int LoNo, trump, lead;

#endif /* table_h */