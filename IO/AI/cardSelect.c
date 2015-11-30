//
//  cardSelect.c
//  Euchre in C
//
//  Created by Chris Matlak on 11/30/15.
//  Copyright © 2015 Euchre US!. All rights reserved.
//

#include "cardSelect.h"

// Choose the correct function for the AI level
int choose_card(player_t computer) {
	h(0.111 * sec);
	switch (computer.AI) {
		case 2:
			return strategic_card(computer);
			break;
		case 1:
			return best_card(computer);
			break;
		case -1:
			return play_random_card(computer);
			break;
		case -2:
			return strategic_card(computer);
			break;
		case -3:
			return best_card(computer);
			break;
		case -4:
			return strategic_card(computer);
			break;
			
		default:
			return play_random_card(computer);
			break;
	}
	return play_random_card(computer); // Have I made it clear what the fallback option is?
}

// AI level 1
// Pick the highest-value (or lowest in LoNo) card possible without beating your partner (usually)
// If your highest card is already beaten, pick a bad card
int best_card(player_t computer) {
	return play_random_card(computer);
}

// AI level 2
// Keep track of cards previously played and plays the worst guarenteed winning card (try to save the highest cards for the end)
int strategic_card(player_t computer) {
	return best_card(computer);
}

void get_valid_cards(card_t hand[], int validCardAry[]) {
	int count=0;
	for (int i=0; i<12-trickNumber; i++) {
		if (is_valid_card(hand, hand[i])) {
			validCardAry[count]=i;
			count++;
		}
	}
}

// Picks the worst card for throwing away
int bad_card(player_t computer) {
	return 0;
}

int play_random_card(player_t computer) {
	while (1) {
		int loc = random_int(12-trickNumber);
		if (is_valid_card(computer.hand, computer.hand[loc]))
			return loc;
	}
	return -25;
}