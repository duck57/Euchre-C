//
//  cardSelect.h
//  Euchre in C
//
//  Created by Chris J.M. on 11/30/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef cardSelect_h
#define cardSelect_h

#include <stdio.h>
#include "table.h"
#include "deckOps.h"
#include "scoring.h"

int choose_card(player_t computer);
void get_valid_cards(card_t hand[], int validCardAry[]);
int best_card(player_t computer);
int strategic_card(player_t computer);

int play_random_card(const card_t hand[]);
int bad_card(player_t computer);

int lead_l1(const card_t hand[], const int remainingCards);

#endif /* cardSelect_h */
