//
//  ai.h
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

/*
 AI CLASSES:
 2 - Calculates number of guaranteed tricks for bet, keeps track of remaining cards when deciding what to play, bets strategically
 1 - Simple look at hand when betting, plays the best card possible (while trying not to beat partner)
 0 - Human: see humanIO.c
 -1 - random bid, trump, and card (valid card only)
 -2 - random bid & trump, plays best (strategic) card
 -3 - random bid & trump, plays highest valid card
 -4 - random bid, but selects the best (stategic) trump and card
 */

#ifndef Euchre_ai_h
#define Euchre_ai_h

#include "bet.h"
#include "bet.h"
#include "call.h"
#include "cardSelect.h"

#endif
