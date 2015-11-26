//
//  DeckOperations.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "DeckOps.h"

void deal() {
	make_double_euchre_deck(euchreDeck);
	shuffle_deck();
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 12; j++) {
			playerList[i].hand[j].colour = euchreDeck[k].colour;
			playerList[i].hand[j].rank = euchreDeck[k].rank;
			k++;
		}
		sort_hand(playerList[i].hand,12);
		playerList[i].tricks = 0;
		generate_bid_list(playerList[i],i);
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

void print_hand(player_t player) {
	for (int i = 0; i < 12; i++) {
		show_card(player.hand[i]);
	}
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

void trump_hand(player_t player, suit_t trump) {
	for (int j=0; j<12; j++) {
		make_card_trump(player.hand[j], trump);
	}
	sort_hand(player.hand,12);
	if (player.AI)
		return;
	
	// Sort trump as if it's part of the rest of the same suit for humans
	for (int j=0; j<12; j++) {
		revert_card(player.hand[j], trump);
	}
	sort_hand(player.hand, 12);
	for (int j=0; j<12; j++) {
		make_card_trump(player.hand[j], trump);
	}
}

void declare_trump(int trump) {
	if (trump==5)
		return;
	if (trump==0) {
		LoNo = 1;
		return;
	}
	for (int i=0; i<4; i++) {
		trump_hand(playerList[i], trump);
	}
}