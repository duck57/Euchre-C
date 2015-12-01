//
//  bet.c
//  Euchre in C
//
//  Created by Chris J.M. on 11/30/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "bet.h"

int random_euchre_bet() {
	int r = random_int(999);
	if (r < 444)	// 44.4%
		return 0;	// Pass
	if (r < 666)	// 22.2%
		return 6;	// 6
	if (r < 757)	// 9.1%
		return 8;	// 8
	if (r < 777)	// 2.0%
		return 12;	// 12
	if (r < 888)	// 11.1%
		return 7;	// 7
	if (r < 911)	// 2.3%
		return 11;	// 11
	if (r < 920)	// 0.9%
		return 20;	// loner
	if (r < 931)	// 1.1%
		return 24;	// shooter
	if (r < 963)	// 3.2%
		return 10;	// 10
					// 3.6%
	return 9;		// 9
}

// This assumes the bidding has already been normalized
int choose_bet(player_t computer, const int currentHibet) {
	h(0.123 * sec);
	
	if (computer.AI < 0)
		return random_euchre_bet();
	
	if (debugAI)
		printf("\t"); print_bids(computer); printf("\t%d\t", computer.bidList[6]);
	
	int testBet = computer.bidList[computer.bidList[6]];
	if (testBet < 6)
		return 0;
	if (testBet > 13)
		return 24; // call a loner
	if (testBet == 13)
		return 20; // call a shooter
	if (currentHibet == 0) {
		if (testBet < 9) {
			return testBet; // safe to call 6, 7, or 8 if you're the first bet
		} else {
			return 5 + testBet/2; // don't want to be too aggressive on the first go
		}
	} else {
		return (testBet+currentHibet+1)/2; // you should try to edge out other players, not give some stupidly high bet for no reason
	}
	return 0;
}

void print_bids(player_t computer) {
	for (int i=0; i<6; i++) {
		printf("%d ",computer.bidList[i]);
	}
}