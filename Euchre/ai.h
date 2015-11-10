//
//  ai.h
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_ai_h
#define Euchre_ai_h

#include "card.h"
#include "euchre.h"

int get_card(player_t human, card_t trick[]);
int choose_card(player_t computer, card_t trick[], int tricksPlayed);
int human_bet();
int computer_bet();
int is_valid_card(card_t hand[], card_t test, card_t trick[]);
int get_trump(player_t hLead);
int choose_trump(player_t cLead);

#endif
