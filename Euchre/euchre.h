//
//  euchre.h
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_euchre_h
#define Euchre_euchre_h

#include <string.h>
#include "card.h"

typedef struct player_t {
    card_t hand[12];
    char *name; // Player name
    int AI; // AI strength of 0 == human player
    int tricks; // how many tricks you took
    int bet; // your bet
    int bidList[6]; // used for AI bidding
} player_t;

// Some shared assets
player_t playerList[4];
card_t euchreDeck[48];
card_t trick[4];
card_t discard[48]; // used for advanced AI
int trickNumber;

/*	Common-knowledge variables are declared here to prevent excessive parameterization
	If it's not intended to me at all malleable, it's declared in euchre.c */
int scoreNS;
int scoreEW;
int betNS;
int betEW;
int LoNo;


// Function declarations
void play_euchre();
void play_hand(int dealer);
int get_bets(int dealer);
int stick_dealer(int dealer);
int play_trick(int lead, int trump);

int make_euchre_trump(int trump);
int is_valid_card(card_t hand[], card_t test);
int score_in_range();


#endif