//
//  humanIO.h
//  Euchre
//
//  Created by Chris Matlak on 11/9/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#ifndef humanIO_h
#define humanIO_h

#include <stdio.h>
#include "euchre.h"
#include "card.h"
#include "table.h"
#include "menus.h"

#endif /* humanIO_h */

int get_bet(player_t human, int currentHibet);
int get_card(player_t human);
void set_options();
int get_trump(player_t human);