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
		generate_bid_list(&playerList[i]);
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

// redirect to generic function
void print_hand(player_t player) {
	print_a_hand(player.hand, 12, trumpSuit);
}

void play_card(const int player, const int cardLoc, const int lead) {
	int pos = mod(player-lead, 4);
	card_t cardPlayed = playerList[player].hand[cardLoc];
	trick[pos] = cardPlayed;
	discard[trickNumber*4+pos] = cardPlayed;
	for (int i = cardLoc; i < 11; i++) {
		playerList[player].hand[i] = playerList[player].hand[i+1];
	}
	playerList[player].hand[11] = make_card(BLANK, NONE);
}

void declare_trump(const int trumpIn) {
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
		trump_hand(playerList[i].hand, 12, trumpSuit, !playerList[i].AI);
	}
}