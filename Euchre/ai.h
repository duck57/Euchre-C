//
//  ai.h
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_ai_h
#define Euchre_ai_h

#include "euchre.h"
#include "DeckOperations.h"


void generate_bid_list(player_t computer, int computer_location);
int choose_card(player_t computer);
int choose_bet(player_t computer, int currentHibet);
int choose_trump(player_t computer);
void print_bids(player_t computer);

#endif
