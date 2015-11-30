//
//  call.c
//  Euchre in C
//
//  Created by Chris Matlak on 11/30/15.
//  Copyright © 2015 Euchre US!. All rights reserved.
//

// trump-declaring functions

#include "call.h"

int random_bidEuchre_trump() {
	return random_int(6);
}

int choose_trump(player_t computer) {
	h(0.099 * sec);
	return (computer.AI > 0 || computer.AI == -4) ? computer.bidList[6] : random_bidEuchre_trump();
}