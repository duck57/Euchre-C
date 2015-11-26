//
//  humanIO.c
//  Euchre
//
//  Created by Chris J.M. on 11/9/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "humanIO.h"

int get_bet(player_t human, int currentHibet) {
	show_hand(human);
	
	return get_number_in_range("Bet? ", 0, 12, 2); //TODO: add validation & help
}

int get_trump(player_t human) {
	return get_number_in_range("Trump ID? ", 0, 5, 1); //TODO: add help
}

int get_card(player_t human) {
	char dNum[3];
	show_stats(human.pos);
	printf("\n\t");
	for (int i=0; i<12-trickNumber; i++) {
		pad_zero(dNum, i, 2);
		printf("%s ", dNum);
	}
	return get_number_in_range("\n\tCard index? ", -1, 12-trickNumber, 2); //TODO: add validation & help
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
	printf("\t%s:\t", display_trump(trump));
	if (compare_card_c(trick[0], make_card(BLANK, NONE), 1, LoNo) == 0)
		printf("Your lead");
	else
		for (int i=0; i<4; i++) {
			show_card(trick[i]);
			printf(" ");
		}
	printf("\n");
}

void show_hand(player_t player) {
	printf("%s:\t",player.name);
	print_hand(player);
	printf("\n");
}