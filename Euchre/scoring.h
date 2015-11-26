//
//  scoring.h
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef scoring_h
#define scoring_h

#include <stdio.h>
#include "initZero.h"
#include "table.h"
#include <string.h>
#include <time.h>

int score_trick(int lead);
void score_hand();
int find_big_card();
void hand_score_update(player_t a, player_t b, int teamBet);

#endif /* scoring_h */