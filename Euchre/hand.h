//
//  hand.h
//  Euchre
//
//  Created by Chris J.M. on 11/28/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

// Functions for dealing with collections of cards

#ifndef hand_h
#define hand_h

#include <stdio.h>
#include "card.h"
#include "shuffle.h"

#endif /* hand_h */

void sort_hand(card_t hand[], const int numberOfCards);
void sort_player_hand(card_t hand[], int numberOfCards, int humanTrumpSorting, suit_t trump);

void trump_hand(card_t hand[], const int handSize, const suit_t trump, const int humanTrumpSorting);
void hand_to_trump(card_t hand[], const int handSize, const suit_t trumpSuit);
void revert_hand(card_t hand[], const int handSize, const suit_t trumpSuit);

void copy_hand(const card_t src[], card_t dst[], const int hand_size);

void print_a_hand(const card_t hand[], const int handSize, const suit_t trumpSuit);

int pick_random_card(const card_t hand[], const int handSize, const suit_t leadSuit);
int high_card(const card_t hand[], const int handSize);
int low_card(const card_t hand[], const int handSize);
int offSuit_Ace(const card_t hand[], const int handSize);
int lowTrump(const card_t hand[], const int handSize);

int biggest_card_ofSuit(const card_t hand[], const int handSize, const
						suit_t suit, const int countTrump);
int small_card_ofSuit(const card_t hand[], const int handSize, const suit_t suit);

int is_valid_card(const card_t hand[], const int loc, const suit_t leadSuit, const int handSize);