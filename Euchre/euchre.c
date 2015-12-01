//
//  euchre.c
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include "euchre.h"


// Game Over Criteria
int maxPointsLost = 50;
int allLoseCondition = -25;
int victoryScore = 50;
int shortcutEuchre = 1; // toggles whether teams that get euchred finish their hand.  Set to -1 to stop the short-cutting of a Loner
int maxGameLength = 99; // to pretent indefinitely-long AI matches

// Default player names
char *NORTH = "NORTH";
char *SOUTH = "SOUTH";
char *EAST = "EAST";
char *WEST = "WEST";

// Returns the winning team
int play_euchre() {
	int hands = 0;
    dealer = random_int(3); // randomly assign the starting dealer
    while (score_in_range()) {
		hands++;
		printf("Hand %d\n", hands);
        dealer = play_hand(dealer);
		h(1.5 * sec);
		if (hands > maxGameLength) {
			printf("\n\nGame went too long.\n\n");
			return -3 * UNINIT; // in case it's a 4-AI game that gets stuck
		}
    }
    if (scoreNS < allLoseCondition && scoreEW < allLoseCondition) {
        printf("\n\nAfter %d hands, you all lose.\n\n", hands);
		return -1;
    } else {
		if (scoreNS > scoreEW) {
			victory_message(1, scoreNS, scoreEW, hands);
			return 1;
		} else {
			victory_message(0, scoreEW, scoreNS, hands);
			return 0;
		}
    }
	return UNINIT; // shold not happen
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

// Returns the next dealer
int play_hand(const int dealer) {
    deal();
    printf("Dealer: %s\t\tScores: NS %d\tEW %d\n", playerList[dealer].name, scoreNS, scoreEW);
	
	//betting and trump selection
    lead = get_bets(dealer);
	trumpCall = pick_a_trump(playerList[lead]);
	char *trumpDisp = display_trump(trumpCall);
    printf("%s.\n\n", trumpDisp); //print trump; lead-in text should be handled in get_bets()
	declare_trump(trumpCall);
	
	// actually play the round
	for (trickNumber=0; trickNumber<12; trickNumber++) {
		printf("Trick %d\n", trickNumber+1);
        lead = play_trick(lead);
		h(0.5 * sec);
    }
	
	// scoring
	score_hand();
	
	return (dealer+1)%4;
}

// Returns the new lead
int play_trick(const int lead) {
	zero_trick();
    for (int p = lead; p < lead+4; p++) {
		play_card(p%4, pick_a_card(playerList[p%4]), lead);
        printf("%s plays ", playerList[p%4].name);
        show_card(trick[p-lead], trumpSuit);
        printf("\n");
    }
	return score_trick(lead);
}

// Returns the location of the player who won the bidding
int get_bets(const int dealer) {
    betEW = 0;
    betNS = 0;
    bids[4] = (dealer+1)%4;
    for (int i = dealer+1; i < dealer+5; i++) {
        int playerBet = 0;
        if ((i-dealer)%4 == 0 && bids[bids[4]] < 6)
            return stick_dealer(dealer);
		playerBet = pick_a_bet(&playerList[i%4], bids[bids[4]]);
		if (playerBet == 24) {
			printf("%s called a loner!\n", playerList[i%4].name);
			alone = 1;
			return i%4; //end bidding once someone calls a loner
		}
        if (playerBet > bids[bids[4]]) {
			bids[4] = i%4;
            bids[bids[4]] = playerBet;
            printf("%s bet %d\n", playerList[bids[4]].name, playerBet);
        } else {
            printf("%s passes\n", playerList[i%4].name);
        }
    }
	set_bets(bids[4], bids[bids[4]]);
	return bids[4];
}


void set_bets(const int winningPlayerLoc, int winningBet) {
	printf("%s won a bet of %d and called ", playerList[winningPlayerLoc].name, winningBet); //trump listed later on
	if (winningBet == 20) {
		alone = 1;
		winningBet = 12;
	} else if (winningBet == 24) {
		alone = 2;
		winningBet = 12;
	}
	if (winningPlayerLoc%2 == 0)
		betEW = winningBet;
	else
		betNS = winningBet;
}


int stick_dealer(const int dealer) {
	if (playerList[dealer].AI == 0)
		print_hand(playerList[dealer]);
    if (dealer%2!=0) {
        betNS = 6;
    } else {
        betEW = 6;
    }
    printf("Stuck dealer!  %s declares ",playerList[dealer].name);
    return dealer;
}