//
//  DeckOperations.c
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "DeckOperations.h"

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

void show_hand(player_t player) {
	printf("%s:\t",player.name);
	for (int i = 0; i < 12; i++) {
		show_card(player.hand[i]);
	}
	if (player.AI == 0)
		printf("*");
	printf("\n");
}

void show_stats(int player) {
	if (player%2!=0) {
		printf("\t %d Us\t", scoreNS);
		printf("\tYou %d %d Part\t", playerList[player].tricks, playerList[(player+2)%4].tricks);
		printf("\t Them %d\n", scoreEW);
	} else {
		printf("\t %d Us\t", scoreEW);
		printf("\tYou %d %d Part\t", playerList[player].tricks, playerList[(player+2)%4].tricks);
		printf("\t Them %d\n", scoreNS);
	}
	show_hand(playerList[player]);
}

void play_card(int player, int cardLoc, int lead) {
	int pos = (player+lead)%4;
	card_t cardPlayed = playerList[player].hand[cardLoc];
	trick[pos] = cardPlayed;
	discard[trickNumber*4+pos] = cardPlayed;
	for (int i = cardLoc; i < 11; i++) {
		playerList[player].hand[i] = playerList[player].hand[i + 1];
	}
	playerList[player].hand[11] = make_card(BLANK, NONE);
}