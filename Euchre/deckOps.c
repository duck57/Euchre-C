//
//  DeckOperations.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "DeckOps.h"

void deal() {
	alone = 0;
	LoNo = 0;
	for (int i=0; i<5; i++) {
		bids[i] = 0;
	}
	make_double_euchre_deck(euchreDeck);
	shuffle_deck();
	
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 12; j++) {
			playerList[i].hand[j] = euchreDeck[k];
			k++;
		}
		sort_hand(playerList[i].hand, 12);
		playerList[i].tricks = 0;
		generate_bid_list(playerList[i], i);
	}
}

void shuffle_deck() {
	for (int i = 0; i < foo4random(); i++) {
		shuffle(euchreDeck, 48, sizeof(euchreDeck[0]));
	}
}

void make_double_euchre_deck(card_t euchreDeck[]) {
	int i,j,k = 0;
	for (i = 1; i < 5; i++) {
		for (j = 9; j < 15; j++) {
			euchreDeck[k] = make_card(i, j);
			k++;
		}
	}
	for (i = 1; i < 5; i++) {
		for (j = 9; j < 15; j++) {
			euchreDeck[k] = make_card(i, j);
			k++;
		}
	}
}

void make_euchre_deck(card_t euchreDeck[]) {
	int i,j,k = 0;
	for (i = 1; i < 5; i++) {
		for (j = 9; j < 15; j++) {
			euchreDeck[k] = make_card(i, j);
			k++;
		}
	}
}

// redirect to hand-specific function
void print_hand(player_t player) {
	print_a_hand(player.hand, 12, trumpSuit);
}

void play_card(int player, int cardLoc, int lead) {
	int pos = mod(player-lead, 4);
	card_t cardPlayed = playerList[player].hand[cardLoc];
	trick[pos] = cardPlayed;
	discard[trickNumber*4+pos] = cardPlayed;
	for (int i = cardLoc; i < 11; i++) {
		playerList[player].hand[i] = playerList[player].hand[i+1];
	}
	playerList[player].hand[11] = make_card(BLANK, NONE);
}

// Can't move this to hand.c because it requires knowledge of the first card played for the trick
int is_valid_card(card_t hand[], card_t test) {
	// Don't play blank spaces
	if (test.colour == BLANK || test.rank == NONE)
		return 0;
	// Any card is good if it's your lead
	if (trick[0].colour == BLANK || trick[0].rank == NONE)
		return 1;
	// It's a valid card if it matches suit with the lead
	if (test.colour == trick[0].colour)
		return 1;
	// Checks that you don't have any cards matching the suit of the first card
	for (int i = 0; i < 12; i++) {
		if (hand[i].colour == trick[0].colour)
			return 0;
	}
	// If everything else checks out…
	return 1;
}


void declare_trump(int trumpIn) {
	// no one should have cards of type "trump" in their hand when trump is delcared
	// This may need to change if we use this is the base for non-Euchre games
	trumpSuit = TRUMP;

	switch (trumpIn) {
		case 0:
			LoNo = 1;
			return;
			break;
		case 1:
			trumpSuit = CLUBS;
			break;
		case 2:
			trumpSuit = DIAMONDS;
			break;
		case 3:
			trumpSuit = SPADES;
			break;
		case 4:
			trumpSuit = HEARTS;
			break;
		case 5:
			return;
			
		default:
			printf("\nTrump error.\n");
			return;
			break;
	}
	
	for (int i=0; i<4; i++) {
		//trump_hand(playerList[i].hand, 12, trumpSuit, !playerList[i].AI); // this doesn't seem to work, using brute force here
		make_hand_trump(i, trumpSuit);
	}
}

// Because the hand.c implementation isn't working
void make_hand_trump(int playerID, suit_t trump) {
	for (int j=0; j<12; j++) {
		playerList[playerID].hand[j] = make_card_trump(playerList[playerID].hand[j], trumpSuit);
	}
	sort_hand(playerList[playerID].hand, 12);
	if (playerList[playerID].AI)
		return;
	
	// Human-like sorting
	for (int j=0; j<12; j++) {
		playerList[playerID].hand[j] = revert_card(playerList[playerID].hand[j], trumpSuit);
	}
	sort_hand(playerList[playerID].hand, 12);
	for (int j=0; j<12; j++) {
		playerList[playerID].hand[j] = make_card_trump(playerList[playerID].hand[j], trumpSuit);
	}
}