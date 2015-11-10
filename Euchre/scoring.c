//
//  scoring.c
//  Euchre
//
//  Created by Chris Matlak on 11/10/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "scoring.h"


int score_trick() {
	int bigCardLoc = 0;
	for (int i=1; i<4; i++) {
		if (compare_card_c(trick[i], trick[bigCardLoc], 1, LoNo) > 0 && follow_suit(trick[i],trick[0].colour))
			bigCardLoc = i;
	}
	return bigCardLoc;
}

void score_hand() {
	if (betNS == 0) {
		hand_score_update(playerList[0], playerList[2], betEW);
		if (playerList[0].tricks + playerList[2].tricks < betEW)
			scoreEW = scoreEW - betEW;
		else
			scoreEW = scoreEW + playerList[0].tricks + playerList[2].tricks + 2;
	} else {
		hand_score_update(playerList[1], playerList[3], betNS);
		if (playerList[1].tricks + playerList[3].tricks < betNS)
			scoreNS = scoreNS - betNS;
		else
			scoreNS = scoreNS + playerList[1].tricks + playerList[3].tricks + 2;
	}
	zero_discard();
}

void hand_score_update(player_t a, player_t b, int teamBet) {
	printf("%s and %s made a bet of %d and got %d and %d tricks, respectively.\n", a.name, b.name, teamBet, a.tricks, b.tricks);
}