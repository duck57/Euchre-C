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
#include "scoring.h"
#include "IOsplitter.h"
#include "deckOps.h"
#include "setup.h"


// Function declarations
void play_euchre();
void play_hand(int dealer);
int get_bets(int dealer);
int stick_dealer(int dealer);
int play_trick(int lead);

int make_euchre_trump(int trump);
int score_in_range();
void set_bets(int winningPlayerLoc, int winningBet);
void victory_message(int winningTeam, int winningScore, int loserScore, int numberOfHands);


#endif