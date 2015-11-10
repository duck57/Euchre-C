//
//  IOsplitter.c
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "IOsplitter.h"

int pick_a_bet(player_t player) {
	if (player.AI)
		return choose_bet(player);
	else
		return get_bet(player);
	return -5; // ERROR!
}

int pick_a_trump(player_t lead) {
	if (lead.AI)
		return choose_trump(lead);
	else
		return get_trump(lead);
	return -55; // error
}

int pick_a_card(player_t player) {
	if (player.AI) {
		return choose_card(player);
	} else {
		//show_stats(i%4);
		return get_card(player);
	}
	return -99; // error
}