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
#include "hand.h"

void deal();
void shuffle_deck();
void make_double_euchre_deck(card_t euchreDeck[]);
void make_euchre_deck(card_t euchreDeck[]);
void play_card(int player, int cardLoc, int lead);
int is_valid_card(card_t hand[], card_t test);
void declare_trump(int trumpIn);
void print_hand(player_t player);

// Replacement functions for hand.c
void make_hand_trump(int playerID, suit_t trump);

#endif /* DeckOperations_h */