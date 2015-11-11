//
//  euchre.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "euchre.h"
#include "scoring.h"
#include "IOsplitter.h"
#include "DeckOperations.h"
#include "initZero.h"

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
    printf("Welcome to double-deck euchre!\n\n");
    init_players();
    
    int dealer = 0;
    while (score_in_range()) {
        play_hand(dealer);
        dealer = (dealer+1)%4;
    }
    if (scoreNS < -25 && scoreEW < -25) {
        printf("\n\nYou both lose.\n\n");
    } else {
        if (scoreNS > scoreEW) {
            printf("\n\n%s and %s win %d to %d!\n", playerList[1].name, playerList[3].name, scoreNS, scoreEW);
            printf("Better luck next time, %s and %s.\n", playerList[0].name, playerList[2].name);
        } else {
            printf("\n\n%s and %s win %d to %d!\n", playerList[0].name, playerList[2].name, scoreEW, scoreNS);
            printf("Better luck next time, %s and %s.\n", playerList[3].name, playerList[1].name);
        }
    }
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
	if (scoreEW > allLoseCondition) {
		return 1;
	}
	if (scoreNS > allLoseCondition) {
		return 1;
	}
	return 0;
}

void play_hand(int dealer) {
    deal();
    printf("Dealer: %s\t\tScores: NS %d\tEW %d\n", playerList[dealer].name, scoreNS, scoreEW);
	ls=0;
	
	//betting and trump selection
    int lead = get_bets(dealer);
	int trump = pick_a_trump(playerList[lead]);
    char *trumpDisp;
    if (trump == 0) {
        trumpDisp = "LoNo";
		LoNo = 1;
    } else if (trump == 5) {
        trumpDisp = "HiNo";
    } else {
        trumpDisp = display_suit((suit_t) trump);
    }
    printf("%s (%d).\n", trumpDisp, trump); //print trump; lead-in text should be handled in get_bets()
	
	// actually play the round
	for (trickNumber=0; trickNumber<12; trickNumber++) {
        lead = play_trick(lead, trump);
    }
	
	// scoring
	score_hand();
}

int play_trick(int lead, int trump) {
    //printf("%s is lead.\n", playerList[lead].name);
	
    //gather cards
	zero_trick();
    for (int i = lead; i < lead+4; i++) {
		play_card(i%4, pick_a_card(playerList[i%4]), lead);
        //printf("%s plays ", playerList[i%4].name);
        //show_card(trick[(i-lead)%4]);
        //printf("\n");
    }
    
    //score cards
    int bigCardLoc = score_trick();
    int newLead = (lead+bigCardLoc)%4;
    playerList[newLead].tricks++;
	zero_trick();
    //printf("%s won\n\n", playerList[newLead].name);
    return newLead;
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


int make_euchre_trump(int trump) {
    if (trump == 0) {
        LoNo = 1;
        return trump;
    } else if (trump == 5) {
        LoNo = 0;
        return trump;
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            if (playerList[i].hand[j].colour == trump) {
                //make_trump(playerList[i].hand[j]);
                playerList[i].hand[j].colour = TRUMP;
                if (playerList[i].hand[j].rank == JACK)
                    playerList[i].hand[j].rank = RIGHT;
            } else if (playerList[i].hand[j].rank == JACK) {
                switch (trump) {
                    case 1:
                        if (playerList[i].hand[j].colour == SPADES) {
                            playerList[i].hand[j].colour = TRUMP;
                            playerList[i].hand[j].rank = LEFT;
                        }
                        break;
                    case 2:
                        if (playerList[i].hand[j].colour == HEARTS) {
                            playerList[i].hand[j].colour = TRUMP;
                            playerList[i].hand[j].rank = LEFT;
                        }
                        break;
                    case 3:
                        if (playerList[i].hand[j].colour == CLUBS) {
                            playerList[i].hand[j].colour = TRUMP;
                            playerList[i].hand[j].rank = LEFT;
                        }
                        break;
                    case 4:
                        if (playerList[i].hand[j].colour == DIAMONDS) {
                            playerList[i].hand[j].colour = TRUMP;
                            playerList[i].hand[j].rank = LEFT;
                        }
                        break;
                        
                    default:
                        
                        break;
                }
            }
        }
        sort_hand(playerList[i].hand,12);
    }
    
    LoNo = 0;
    return trump;
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

int is_valid_card(card_t hand[], card_t test) {
	// Don't play blank spaces
	if (test.colour == BLANK || test.rank == NONE)
		return 0;
	// Any card is good if it's your lead
	if (trick[0].colour == BLANK || trick[0].rank == NONE)
		return 1;
	if (test.colour == trick[0].colour || test.colour == TRUMP)
		return 1;
	// Checks that you don't have any cards matching the suit of the first card
	for (int i = 0; i < 12; i++) {
		if (hand[i].colour == trick[0].colour)
			return 0;
	}
	// If everything else checks out…
	return 1;
}