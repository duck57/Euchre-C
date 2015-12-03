//
//  IOsplitter.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "IOsplitter.h"

int pick_a_bet(player_t *player, int currentHibet) {
	return player->AI ? choose_bet(*player, currentHibet) : get_bet(*player, currentHibet);
}

int pick_a_trump(player_t lead) {
	return lead.AI ? choose_trump(lead) : get_trump(lead);
}

int pick_a_card(player_t player) {
	if (trickNumber == 11) { // final trick, only one card to play
		h(0.1 * sec);
		return 0;
	}
	return player.AI ? choose_card(player) : get_card(player);
}