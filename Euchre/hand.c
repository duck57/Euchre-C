//
//  hand.c
//  Euchre
//
//  Created by Chris J.M. on 11/28/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "hand.h"

void sort_hand(card_t hand[], int numberOfCards) {
	int cardSize = sizeof(card_t);
	qsort(hand, numberOfCards, cardSize, compare_card);
}

void sort_player_hand(card_t hand[], int numberOfCards, int humanTrumpSorting, suit_t trump) {
	sort_hand(hand, numberOfCards);
	if (humanTrumpSorting == 0)
		return;
	
	// Sort trump as if it's the display suit
	revert_hand(hand, numberOfCards, trump);
	sort_hand(hand, numberOfCards);
	hand_to_trump(hand, numberOfCards, trump);
}

//this doesn't seem to work
void trump_hand(card_t hand[], int handSize, suit_t trump, int humanTrumpSorting) {
	for (int j=0; j<handSize; j++) {
		make_card_trump(hand[j], trump);
	}
	sort_player_hand(hand, handSize, 0, trump);
}

void print_a_hand(card_t hand[], int handSize, suit_t trumpSuit) {
	for (int i = 0; i < handSize; i++) {
		show_card(hand[i], trumpSuit);
		//show_card(hand[i], TRUMP); // test to see if trump is displayed
		printf("\t");
	}
}

void hand_to_trump(card_t hand[], int handSize, suit_t trumpSuit) {
	for (int i=0; i<handSize; i++) {
		hand[i] = make_card_trump(hand[i], trumpSuit);
	}
}

void revert_hand(card_t hand[], int handSize, suit_t trumpSuit) {
	for (int i=0; i<handSize; i++) {
		hand[i] = revert_card(hand[i], trumpSuit);
	}
}