//
//  cardSelect.h
//  Euchre in C
//
//  Created by Chris Matlak on 11/30/15.
//  Copyright © 2015 Euchre US!. All rights reserved.
//

#ifndef cardSelect_h
#define cardSelect_h

#include <stdio.h>
#include "table.h"
#include "deckOps.h"

int choose_card(player_t computer);
void get_valid_cards(card_t hand[], int validCardAry[]);
int play_random_card(player_t computer);
int best_card(player_t computer);
int strategic_card(player_t computer);
int bad_card(player_t computer);

#endif /* cardSelect_h */
