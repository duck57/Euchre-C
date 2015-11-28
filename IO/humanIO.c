//
//  humanIO.c
//  Euchre
//
//  Created by Chris J.M. on 11/9/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "humanIO.h"

int get_bet(player_t human, int currentHibet) {
	int bet = UNINIT;
	
	// Turn me into a string bean! // I should not code at 4AM, especially after enjoying brandy
	char betText[99] = "Bet (";
	char betHelp[44] = "";
	if (currentHibet) {
		strlcat(betHelp, "must beat ", sizeof(betHelp));
		strlcat(betHelp, numStr_int(currentHibet), sizeof(betHelp));
		strlcat(betText, betHelp, sizeof(betText));
	} else {
		strlcat(betHelp, "6 or greater", sizeof(betHelp));
		strlcat(betText, betHelp, sizeof(betText));
	}
	strlcat(betText, "): ", sizeof(betText));
	
	// Don't go bidding 4
	if (!currentHibet)
		currentHibet = 5;
	
	show_hand(human);
	
	while (bet == UNINIT) {
		bet = get_number_in_range(betText, -2, 12, 2);
		if (bet == ENTERED * UNINIT || bet == -2)
			return choose_bet(human, currentHibet);
		if (bet == HELP * UNINIT)
			h_betting();
		if (bet == -1 || bet == NOTHING * UNINIT)
			return random_euchre_bet();
		if (bet < 0)
			bet = UNINIT;
		if (bet > 0 && bet <= currentHibet) {
			if (currentHibet==5)
				printf("\tMinimum bid is 6.\n");
			else
				printf("\tMust beat the current high bet.  Enter 0 to pass.\n");
			bet = UNINIT;
		}
	}
	return bet;
}

int get_trump(player_t human) {
	int trumpID = UNINIT;
	while (trumpID == UNINIT) {
		trumpID = get_number_in_range("Trump ID? ", 0, 5, 1);
		if (trumpID == HELP * UNINIT)
			h_trump();
		if (trumpID < 0)
			trumpID = UNINIT;
	}
	return trumpID;
}

int get_card(player_t human) {
	char dNum[3];
	show_stats(human.pos);
	printf("\n\t");
	for (int i=0; i<12-trickNumber; i++) {
		pad_zero(dNum, i, 2);
		printf("%d\t", i);
	}
	
	int cardLoc = UNINIT;
	while (cardLoc == UNINIT) {
		cardLoc = get_number_in_range("\n\tCard index? ", -1, 11-trickNumber, 2);
		if (cardLoc == HELP * UNINIT) {
			h_playcard();
			cardLoc = UNINIT;
		}
		if (cardLoc == ENTERED * UNINIT || cardLoc == NOTHING * UNINIT)
			return play_random_card(human);
		if (cardLoc == -1)
			return choose_card(human);
		if (is_valid_card(human.hand, human.hand[cardLoc]))
			return cardLoc;
		if (cardLoc > -1 && cardLoc < 12)
			printf("\t\tYou must follow suit.");
		cardLoc = UNINIT;
	}
	return play_random_card(human);
}

void show_stats(int player) {
	if (player%2 != 0)
		stat_text(player, betNS, betEW);
	else
		stat_text(player, betEW, betNS);
	printf("\t");
	print_hand(playerList[player]);
}

void stat_text(int playerNum, int yourBet, int theirBet) {
	if (yourBet)
		printf("\tWe bet %d", yourBet);
	else
		printf("\tThey bet %d", theirBet);
	printf("\t\t%s %d ", "You", playerList[playerNum].tricks);
	printf("%d %s\n", playerList[(playerNum+2)%4].tricks, playerList[(playerNum+2)%4].name);
	printf("\t%s:\t", display_trump(trumpCall));
	if (compare_card_c(trick[0], make_card(BLANK, NONE), 1, LoNo) == 0)
		printf("Your lead");
	else
		for (int i=0; i<4; i++) {
			show_card(trick[i], trumpSuit);
			printf("\t");
		}
	printf("\n");
}

void show_hand(player_t player) {
	printf("%s:\t",player.name);
	print_hand(player);
	printf("\n");
}