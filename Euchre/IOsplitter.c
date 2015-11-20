//
//  IOsplitter.c
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "IOsplitter.h"

int pick_a_bet(player_t player, int currentHibet) {
	return player.AI ? choose_bet(player, currentHibet) : get_bet(player, currentHibet);
}

int pick_a_trump(player_t lead) {
	return lead.AI ? choose_trump(lead) : get_trump(lead);
}

int pick_a_card(player_t player) {
	return player.AI ? choose_card(player) : get_card(player);
}