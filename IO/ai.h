//
//  ai.h
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#ifndef Euchre_ai_h
#define Euchre_ai_h

#include <stdio.h>
#include "euchre.h"
#include "deckOps.h"
#include "table.h"


void generate_bid_list(player_t computer, int computer_location);
int choose_card(player_t computer);
int choose_bet(player_t computer, int currentHibet);
int choose_trump(player_t computer);
void print_bids(player_t computer);
int random_euchre_bet();
int random_bidEuchre_trump();
int play_random_card(player_t computer);
void get_valid_cards(card_t hand[], int validCardAry[]);


#endif
