//
//  bid.h
//  Euchre in C
//
//  Created by Chris Matlak on 11/30/15.
//  Copyright © 2015 Euchre US!. All rights reserved.
//

#ifndef bid_h
#define bid_h

#include <stdio.h>
#include "table.h"
#include "deckOps.h"

void calculate_tricks(player_t *computer);
void analyse_cards(player_t *computer);
void generate_bid_list(player_t *computer);
void select_best_bet(player_t *computer);

#endif /* bid_h */
