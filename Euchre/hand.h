//
//  hand.h
//  Euchre
//
//  Created by Chris J.M. on 11/28/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef hand_h
#define hand_h

#include <stdio.h>
#include "card.h"
#include "shuffle.h"

#endif /* hand_h */

void sort_hand(card_t hand[], int numberOfCards);
void trump_hand(card_t hand[], int handSize, suit_t trump, int humanTrumpSorting);
void print_a_hand(card_t hand[], int handSize, suit_t trumpSuit);
void sort_player_hand(card_t hand[], int numberOfCards, int humanTrumpSorting, suit_t trump);
void hand_to_trump(card_t hand[], int handSize, suit_t trumpSuit);
void revert_hand(card_t hand[], int handSize, suit_t trumpSuit);