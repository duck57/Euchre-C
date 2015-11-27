//
//  humanIO.h
//  Euchre
//
//  Created by Chris J.M. on 11/9/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef humanIO_h
#define humanIO_h

#include <stdio.h>
#include "euchre.h"
#include "card.h"
#include "table.h"
#include "menus.h"
#include "ai.h" // for calls to AI functions for defaults
#include "help.h"

int get_bet(player_t human, int currentHibet);
int get_card(player_t human);
void set_options();
int get_trump(player_t human);
void show_stats(int player);
void stat_text(int playerNum, int yourScore, int theirScore);
void show_hand(player_t player);

#endif /* humanIO_h */