//
//  DeckOperations.h
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#ifndef DeckOperations_h
#define DeckOperations_h

#include <stdio.h>
#include "card.h"
#include "euchre.h"
#include "shuffle.h"
#include "ai.h"

#endif /* DeckOperations_h */


void deal();
void shuffle_deck();
void make_double_euchre_deck(card_t euchreDeck[]);
void make_euchre_deck(card_t euchreDeck[]);
void show_hand(player_t player);
void show_stats(int player);
void play_card(int player, int cardLoc, int lead);