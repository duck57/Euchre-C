//
//  humanIO.c
//  Euchre
//
//  Created by Chris Matlak on 11/9/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "humanIO.h"
#include "ai.h"
#include "help.h"

int get_bet(player_t human, int currentHibet) {
	return choose_bet(human, currentHibet); //replace this with actual menu drivers
}

int get_card(player_t human) {
	return choose_card(human); //temporary redirect until later
}

void set_options() {
	
}

int get_trump(player_t human) {
	return choose_trump(human); //temporary redirect until later
}