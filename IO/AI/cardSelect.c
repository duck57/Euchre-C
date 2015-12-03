//
//  cardSelect.c
//  Euchre in C
//
//  Created by Chris J.M. on 11/30/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
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
			return play_random_card(computer.hand);
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
			return play_random_card(computer.hand);
			break;
	}
	return play_random_card(computer.hand); // Have I made it clear what the fallback option is?
}

// AI level 1
// Pick the highest-value (or lowest in LoNo) card possible without beating your partner (usually)
// If your highest card is already beaten, pick a bad card
int best_card(player_t computer) {
	card_t bestCard = trick[find_big_card()];
	int remainingCards = 12-trickNumber;
	int i = LoNo ? remainingCards-1 : 0;
	
	if (computer.pos == lead)
		lead_l1(computer.hand, remainingCards);
	
	while (i > -1 && i < remainingCards) {
		if (is_valid_card(computer.hand, i, trick[0].colour, remainingCards)) {
			if (compare_card_c(computer.hand[i], bestCard, 1, LoNo) > 0)
				return i;
		}
		if (LoNo)
			i--;
		else
			i++;
	}
	return play_random_card(computer.hand); //fallback
}

int lead_l1(const card_t hand[], const int remainingCards) {
	if (trumpCall > 0 && trumpCall < 5)
		return offSuit_Ace(hand, remainingCards); // off-suit aces are usually a good lead
	if (LoNo)
		return low_card(hand, remainingCards); // or 9s if you're in LoNo
	return high_card(hand, remainingCards); // aces (any suit) if you're HiNo
}

// AI level 2
// Keep track of cards previously played and plays the worst guarenteed winning card (try to save the highest cards for the end)
int strategic_card(player_t computer) {
	
	
	return best_card(computer); //fallback
}

// This isn't actually used for anything, but is called for now
void get_valid_cards(card_t hand[], int validCardAry[]) {
	int count=0;
	for (int i=0; i<12-trickNumber; i++) {
		if (is_valid_card(hand, i, trick[0].colour, 12-trickNumber)) {
			validCardAry[count]=i;
			count++;
		}
	}
}

// Picks the worst card for throwing away
int bad_card(player_t computer) {
	return 0;
}

// Leaving here as a redirect, since this gets called from so many places
int play_random_card(const card_t hand[]) {
	return pick_random_card(hand, 12-trickNumber, trick[0].colour);
}