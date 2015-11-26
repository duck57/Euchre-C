//
//  euchre.c
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include <stdio.h>
#include "euchre.h"


// Game Over Criteria
int maxPointsLost = 50;
int allLoseCondition = -25;
int victoryScore = 50;

// Default player names
char *NORTH = "NORTH";
char *SOUTH = "SOUTH";
char *EAST = "EAST";
char *WEST = "WEST";

int ls;

void play_euchre() {
	greet();
	set_players();
	
	int hands = 0;
    int dealer = 0;
    while (score_in_range()) {
        play_hand(dealer);
        dealer = (dealer+1)%4;
		hands++;
		h(1.5);
    }
    if (scoreNS < allLoseCondition && scoreEW < allLoseCondition) {
        printf("\n\nAfter %d hands, you all lose.\n\n", hands);
    } else {
        if (scoreNS > scoreEW)
			victory_message(1, scoreNS, scoreEW, hands);
        else
			victory_message(0, scoreEW, scoreNS, hands);
    }
}

// winningTeam is 0 for East & West, 1 for North & South
void victory_message(int winningTeam, int winningScore, int loserScore, int numberOfHands) {
	printf("\n\n%s and %s win %d to %d after %d hands!\n", playerList[winningTeam].name, playerList[winningTeam+2].name, winningScore, loserScore, numberOfHands);
	printf("Better luck next time, %s and %s.\n", playerList[winningTeam+1].name, playerList[(winningTeam+3)%4].name);
}


int score_in_range() {
	// Game Over if a team won
	if (scoreEW > victoryScore) {
		return 0;
	}
	if (scoreNS > victoryScore) {
		return 0;
	}
	// Mercy Rule if a team takes too many negative points
	if (scoreNS < -maxPointsLost) {
		return 0;
	}
	if (scoreEW < -maxPointsLost) {
		return 0;
	}
	// If both teams have enough of a negative score, they both lose
	if (scoreEW > allLoseCondition - 1) {
		return 1;
	}
	if (scoreNS > allLoseCondition - 1) {
		return 1;
	}
	return 0;
}

void play_hand(int dealer) {
    deal();
    printf("Dealer: %s\t\tScores: NS %d\tEW %d\n", playerList[dealer].name, scoreNS, scoreEW);
	ls=0;
	LoNo=0;
	
	//betting and trump selection
    lead = get_bets(dealer);
	trump = pick_a_trump(playerList[lead]);
	char *trumpDisp = display_trump(trump);
    printf("%s.\n\n", trumpDisp); //print trump; lead-in text should be handled in get_bets()
	if (trump ==0)
		LoNo = 1;
	
	// actually play the round
	for (trickNumber=0; trickNumber<12; trickNumber++) {
        lead = play_trick(lead);
		h(0.5);
    }
	
	// scoring
	score_hand();
}

int play_trick(int lead) {
	zero_trick();
    for (int p = lead; p < lead+4; p++) {
		play_card(p%4, pick_a_card(playerList[p%4]), lead);
        printf("%s plays ", playerList[p%4].name);
        show_card(trick[p-lead]);
        printf("\n");
    }
	return score_trick(lead);
}

int get_bets(int dealer) {
    int currentHighbet = 0;
    betEW = 0;
    betNS = 0;
    int where = (dealer + 1)%4;
    for (int i = dealer+1; i < dealer+5; i++) {
        int playerBet = 0;
        if ((i-dealer)%4 == 0 && currentHighbet < 6)
            return stick_dealer(dealer);
		playerBet = pick_a_bet(playerList[i%4], currentHighbet);
        if (playerBet > currentHighbet) {
            currentHighbet = playerBet;
            where = i%4;
            printf("%s bet %d\n", playerList[where].name, playerBet);
        } else {
            printf("%s passes\n", playerList[i%4].name);
        }
    }
	set_bets(where, currentHighbet);
	return where;
}

void set_bets(int winningPlayerLoc, int winningBet) {
	printf("%s won a bet of %d and called ", playerList[winningPlayerLoc].name, winningBet); //trump listed later on
	if (winningBet==20) {
		ls=1;
		winningBet=12;
	} else if (winningBet==24) {
		ls=2;
		winningBet=12;
	}
	if (winningPlayerLoc%2 == 0)
		betEW = winningBet;
	else
		betNS = winningBet;
}


int stick_dealer(int dealer) {
    if (dealer%2!=0) {
        betNS = 6;
    } else {
        betEW = 6;
    }
    printf("Stuck dealer!  %s declares ",playerList[dealer].name);
    return dealer;
}