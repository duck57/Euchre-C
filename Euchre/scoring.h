//
//  scoring.h
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#ifndef scoring_h
#define scoring_h

#include <stdio.h>
#include "initZero.h"
#include "table.h"

int score_trick();
void score_hand();
void hand_score_update(player_t a, player_t b, int teamBet);

#endif /* scoring_h */