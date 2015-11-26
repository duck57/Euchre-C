//
//  DeckOperations.h
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef DeckOps_h
#define DeckOps_h

#include <stdio.h>
#include "shuffle.h"
#include "table.h"
#include "ai.h" // to allow for generating the bid array as part of the deal function

void deal();
void shuffle_deck();
void make_double_euchre_deck(card_t euchreDeck[]);
void make_euchre_deck(card_t euchreDeck[]);
void show_hand(player_t player);
void play_card(int player, int cardLoc, int lead);
int is_valid_card(card_t hand[], card_t test);
void trump_hand(player_t player, suit_t trump);
void declare_trump(int trump);
void print_hand(player_t player);


#endif /* DeckOperations_h */