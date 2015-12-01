//
//  euchre.h
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

// The main game logic and flow

#ifndef Euchre_euchre_h
#define Euchre_euchre_h

#include <string.h>
#include "scoring.h"
#include "IOsplitter.h"
#include "deckOps.h"
#include "setup.h"


// Function declarations
int play_euchre();
int play_hand(const int dealer);
int get_bets(const int dealer);
int stick_dealer(const int dealer);
int play_trick(const int lead);
void play_final_trick(const int lead);

int make_euchre_trump(const int trump);
int score_in_range();
void set_bets(const int winningPlayerLoc, int winningBet);
void victory_message(const int winningTeam, const int winningScore, const  int loserScore, int numberOfHands);


#endif