//
//  bet.h
//  Euchre in C
//
//  Created by Chris J.M. on 11/30/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef bid_h
#define bid_h

#include <stdio.h>
#include "table.h"

int random_euchre_bet();
int choose_bet(player_t computer, const int currentHibet);
void print_bids(player_t computer);

#endif /* bid_h */
