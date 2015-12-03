//
//  scoring.c
//  Euchre
//
//  Created by Chris J.M. on 11/10/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#include "scoring.h"


int find_big_card() {
	return LoNo ? small_card_ofSuit(trick, 4, trick[0].colour) : biggest_card_ofSuit(trick, 4, trick[0].colour, 1);
}

// Input is the current lead, output is the new lead
int score_trick(int lead) {
	int bigCardLoc = find_big_card();
	lead = (lead+bigCardLoc)%4;
	playerList[lead].tricks++;
	zero_trick();
	printf("%s won\n\n", playerList[lead].name);
	return lead;
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

void hand_score_update(player_t a, player_t b, const int teamBet) {
	printf("%s and %s bet %d and ", a.name, b.name, teamBet);
	if (a.tricks+b.tricks<teamBet)
		printf("got euchre'd!\n(%d and %d tricks, respectively)\n\n", a.tricks, b.tricks);
	else
		printf("earned %d and %d tricks, respectively.\n\n", a.tricks, b.tricks);
}