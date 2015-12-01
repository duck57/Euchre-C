//
//  DeckOperations.h
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

// Deck operations that are (mostly) Euchre-specific

#ifndef DeckOps_h
#define DeckOps_h

#include <stdio.h>
#include "table.h"
#include "bid.h" // to allow for generating the bid array as part of the deal function

void deal();
void shuffle_deck();
void make_double_euchre_deck(card_t euchreDeck[]);
void make_euchre_deck(card_t euchreDeck[]);
void play_card(const int player, const int cardLoc, const int lead);
void declare_trump(const int trumpIn);
void print_hand(player_t player);

#endif /* DeckOperations_h */