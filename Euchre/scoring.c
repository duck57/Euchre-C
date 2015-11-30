//
//  scoring.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "scoring.h"


int find_big_card() {
	int bigCardLoc = 0;
	for (int i=1; i<4; i++) {
		if (follow_suit(trick[i],trick[0].colour) && (compare_card_c(trick[i], trick[bigCardLoc], 1, LoNo) > 0))
			bigCardLoc = i;
	}
	return bigCardLoc;
}

int score_trick(int lead) {
	int bigCardLoc = find_big_card();
	int newLead = (lead+bigCardLoc)%4;
	playerList[newLead].tricks++;
	zero_trick();
	printf("%s won\n\n", playerList[newLead].name);
	return newLead;
}

void score_hand() {
	if (betNS == 0) {
		hand_score_update(playerList[0], playerList[2], betEW);
		if (playerList[0].tricks + playerList[2].tricks < betEW) {
			if (alone)
				scoreEW -= 18;
			else
				scoreEW -= betEW;
		}
		else {
			if (alone)
				scoreEW += 24;
				else
				scoreEW += playerList[0].tricks + playerList[2].tricks + 2;
		}
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
	printf("%s and %s bet %d and ", a.name, b.name, teamBet);
	if (a.tricks+b.tricks<teamBet)
		printf("got euchre'd!\n(%d and %d tricks, respectively)\n\n", a.tricks, b.tricks);
	else
		printf("earned %d and %d tricks, respectively.\n\n", a.tricks, b.tricks);
}