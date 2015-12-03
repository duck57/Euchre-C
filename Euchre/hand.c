//
//  hand.c
//  Euchre
//
//  Created by Chris J.M. on 11/28/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "hand.h"

void sort_hand(card_t hand[], const int numberOfCards) {
	int cardSize = sizeof(card_t);
	qsort(hand, numberOfCards, cardSize, compare_card);
}

void sort_player_hand(card_t hand[], const int numberOfCards, const int humanTrumpSorting, suit_t trump) {
	sort_hand(hand, numberOfCards);
	if (humanTrumpSorting == 0)
		return;
	
	// Sort trump as if it's the display suit
	revert_hand(hand, numberOfCards, trump);
	sort_hand(hand, numberOfCards);
	hand_to_trump(hand, numberOfCards, trump);
}


void trump_hand(card_t hand[], const int handSize, const suit_t trump, const int humanTrumpSorting) {
	for (int j=0; j<handSize; j++) {
		make_card_trump(&hand[j], trump);
	}
	sort_player_hand(hand, handSize, humanTrumpSorting, trump);
}

void print_a_hand(const card_t hand[], const int handSize, const suit_t trumpSuit) {
	for (int i = 0; i < handSize; i++) {
		show_card(hand[i], trumpSuit);
		printf("\t");
	}
}

// used as a helper for human-like sorting; use trump_hand(4) for making your hand into trump
void hand_to_trump(card_t hand[], const int handSize, const suit_t trumpSuit) {
	for (int i=0; i<handSize; i++) {
		make_card_trump(&hand[i], trumpSuit);
	}
}

void revert_hand(card_t hand[], const int handSize, const suit_t trumpSuit) {
	for (int i=0; i<handSize; i++) {
		revert_card(&hand[i], trumpSuit);
	}
}

void copy_hand(const card_t src[], card_t dst[], const int hand_size) {
	for (int i=0; i<hand_size; i++) {
		dst[i] = src[i];
	}
}

int pick_random_card(const card_t hand[], const int handSize, const suit_t leadSuit) {
	int loc;
	while (1) {
		loc = random_int(handSize);
		if (is_valid_card(hand, loc, leadSuit, handSize))
			return loc;
	}
	return 0; // if all else fails, return the card in position 0
}

// Plays an off-suit ace or king.  If none are found, plays trump, then plays a low card
int offSuit_Ace(const card_t hand[], const int handSize) {
	int haveKing = 0, haveAce = 0, loc = 0;
	
	value_t seekVal = NONE;
	
	for (int i=0; i<handSize; i++) {
		if (is_rank(hand[i], ACE) && is_not_trump(hand[i]))
			haveAce = 1;
		if (is_rank(hand[i], KING) && is_not_trump(hand[i]))
			haveKing = 1;
	}
	
	if (haveAce) {
		seekVal = ACE;
	} else if (haveAce) {
		seekVal = KING;
	}
	
	int tries;
	if (haveAce || haveKing) {
		while (tries < 100) {
			loc = random_int(handSize);
			if (is_rank(hand[loc], seekVal) && is_not_trump(hand[loc]))
				return loc;
			tries++;
		}
	}
	
	return lowTrump(hand, handSize); // make everyone waste trump if you don't have off-suit aces
}


int lowTrump(const card_t hand[], const int handSize) {
	int found, loc, tries;
	for (int i=0; i<handSize; i++) {
		if (is_trump(hand[i]) && hand[i].rank < KING)
			found++;
	}
	
	if (found) {
		while (tries<100) {
			loc = random_int(handSize);
			if (hand[loc].rank < KING && is_trump(hand[loc]))
				return loc;
			tries++;
		}
	}
	
	return low_card(hand, handSize);
}

int high_card(const card_t hand[], const int handSize) {
	int loc;
	value_t highVal = NONE;
	
	for (int i=0; i<handSize; i++) {
		if (hand[i].rank > highVal) {
			highVal = hand[i].rank;
			loc = i;
		}
	}
	
	if (highVal > JACK) {
		while (1) {
			loc = random_int(handSize);
			if (is_rank(hand[loc], highVal))
				return loc;
		}
	}
	
	return pick_random_card(hand, handSize, BLANK);
}

int low_card(const card_t hand[], const int handSize) {
	int loc;
	value_t lowVal = LEFT;
	
	for (int i=0; i<handSize; i++) {
		if (hand[i].rank < lowVal) {
			lowVal = hand[i].rank;
			loc = i;
		}
	}
	
	if (lowVal < QUEEN) {
		while (1) {
			loc = random_int(handSize);
			if (is_rank(hand[loc], lowVal))
				return loc;
		}
	}
	
	return pick_random_card(hand, handSize, BLANK);
}

// Can't move this to hand.c because it requires knowledge of the first card played for the trick
int is_valid_card(const card_t hand[], const int loc, const suit_t leadSuit, const int handSize) {
	// Don't play blank spaces or Jokers
	if (is_suit(hand[loc], BLANK) || is_rank(hand[loc], NONE) || is_suit(hand[loc], JOKER))
		return 0;
	// Any card is good if it's your lead
	if (leadSuit == BLANK || leadSuit == JOKER)
		return 1;
	// It's a valid card if it matches suit with the lead
	if (is_suit(hand[loc], leadSuit))
		return 1;
	// Checks that you don't have any cards matching the suit of the first card
	for (int i = 0; i < handSize; i++) {
		if (is_suit(hand[i], leadSuit))
			return 0;
	}
	// If everything else checks out…
	return 1;
}

int biggest_card_ofSuit(const card_t hand[], const int handSize, const
						suit_t suit, const int countTrump) {
	int bigCardLoc = 0;
	for (int i=0; i<handSize; i++) {
		if (follow_suit(hand[i], suit, countTrump) && (compare_card_c(hand[i], hand[bigCardLoc], 1, 0) > 0)) {
			bigCardLoc = i;
		}
	}
	return bigCardLoc;
}

int small_card_ofSuit(const card_t hand[], const int handSize, const suit_t suit) {
	int smallCardLoc = 0;
	for (int i=0; i<handSize; i++) {
		if (is_suit(hand[i], suit) && (compare_card_c(hand[i], hand[smallCardLoc], 0, 1) > 0)) {
			smallCardLoc = i;
		}
	}
	return smallCardLoc;
}