//
//  euchre.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "euchre.h"
#include "ai.h"

int scoreNS;
int scoreEW;
const int WIN = 50;
int betNS;
int betEW;
int LoNo = 0;
int victoryScore = 50;
int maxPointsLost = 50;
int allLoseCondition = -25;

char *NORTH = "NORTH";
char *SOUTH = "SOUTH";
char *EAST = "EAST";
char *WEST = "WEST";

void play_euchre() {
    printf("Welcome to double-deck euchre!\n");
    init_players();
    
    int dealer = 0;
    while (score_in_range()) {
        play_hand(dealer);
        dealer = (dealer+1)%4;
    }
    if (scoreNS < -25 && scoreEW < -25) {
        printf("You both lose.\n");
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

void deal() {
    make_double_euchre_deck(euchreDeck);
    shuffle_deck();
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            playerList[i].hand[j].colour = euchreDeck[k].colour;
            playerList[i].hand[j].rank = euchreDeck[k].rank;
            k++;
        }
        sort(playerList[i].hand);
        playerList[i].tricks = 0;
    }
}

void sort(card_t hand[]) {
    //int size = 12;
    qsort(hand, 12, sizeof(card_t), compare_card);
}

void shuffle_deck() {
    for (int i = 0; i < foo4random(); i++) {
        shuffle(euchreDeck, 48, sizeof(euchreDeck[0]));
    }
}

void make_double_euchre_deck(card_t euchreDeck[]) {
    int i,j,k = 0;
    for (i = 1; i < 5; i++) {
        for (j = 9; j < 15; j++) {
            euchreDeck[k] = make_card(i, j);
            k++;
        }
    }
    for (i = 1; i < 5; i++) {
        for (j = 9; j < 15; j++) {
            euchreDeck[k] = make_card(i, j);
            k++;
        }
    }
}

void make_euchre_deck(card_t euchreDeck[]) {
    int i,j,k = 0;
    for (i = 1; i < 5; i++) {
        for (j = 9; j < 15; j++) {
            euchreDeck[k] = make_card(i, j);
            k++;
        }
    }
}

void show_hand(player_t player) {
    printf("%s:\t",player.name);
    for (int i = 0; i < 12; i++) {
        show_card(player.hand[i]);
    }
    if (player.isHuman)
        printf("*");
    //    if ()
    printf("\n");
}

void show_stats(int player) {
    if (player%2!=0) {
        printf("\t %d Us\t", scoreNS);
        printf("\tYou %d %d Part\t", playerList[player].tricks, playerList[(player+2)%4].tricks);
        printf("\t Them %d\n", scoreEW);
    } else {
        printf("\t %d Us\t", scoreEW);
        printf("\tYou %d %d Part\t", playerList[player].tricks, playerList[(player+2)%4].tricks);
        printf("\t Them %d\n", scoreNS);
    }
    show_hand(playerList[player]);
}

void play_card(int player, int cardLoc, int lead, card_t trick[]) {
    trick[(player+lead)%4] = playerList[player].hand[cardLoc];
    for (int i = cardLoc; i < 11; i++) {
        playerList[player].hand[i] = playerList[player].hand[i + 1];
    }
    playerList[player].hand[11] = make_card(BLANK, NONE);
}


void zero_players() {
    for (int i = 0; i < 4; i++) {
        playerList[i].isHuman = 0;
        playerList[i].name = "";
        playerList[i].tricks = 0;
        playerList[i].bet = 0;
    }
}

void init_players() {
    zero_players();
	// TODO: Add in manual entry of player names, welcome, and selection of human/computer players
    playerList[0].name = "Amanda"; //EAST
    playerList[1].name = "Chris"; //SOUTH
    playerList[1].isHuman = 1;
    playerList[2].name = "Ben"; //WEST
    playerList[3].name = "Michelle"; //NORTH
}

void play_hand(int dealer) {
    deal();
    printf("Dealer: %s\t\tScores: NS %d\tEW %d\n", playerList[dealer].name, scoreNS, scoreEW);
    int lead = get_bets(dealer);
    int trump = 0;
    if (playerList[lead].isHuman)
        trump = get_trump(playerList[lead]);
    else
        trump = choose_trump(playerList[lead]);
    char *showTrump;
    if (trump == 0) {
        showTrump = "LoNo";
    } else if (trump == 5) {
        showTrump = "HiNo";
    } else {
        showTrump = display_suit((suit_t) trump);
    }
    printf("%s.\n", showTrump); //print trump; lead-in text should be handled in
    for (int i = 0; i < 12; i++) {
        lead = play_trick(lead, trump, i);
    }
    if (betNS != 0) {
        printf("%s and %s made a bet of %d and got %d and %d tricks, respectively.\n", playerList[3].name, playerList[1].name, betNS, playerList[3].tricks, playerList[1].tricks);
        if (playerList[1].tricks + playerList[3].tricks < betNS)
            scoreNS = scoreNS - betNS;
        else
            scoreNS = scoreNS + playerList[1].tricks + playerList[3].tricks + 2;
    } else {
        printf("%s and %s made a bet of %d and got %d and %d tricks, respectively.\n", playerList[0].name, playerList[2].name, betEW, playerList[0].tricks, playerList[2].tricks);
        if (playerList[0].tricks + playerList[2].tricks < betEW)
            scoreEW = scoreEW - betEW;
        else
            scoreEW = scoreEW + playerList[0].tricks + playerList[2].tricks + 2;
    }
}

void reset_trick(card_t* trick) {
	for (int i = 0; i < 4; i++) {
		trick[i] = make_card(BLANK, NONE);
	}
}

int score_trick(card_t trick[4]) {
	int bigCardLoc = 0;
	for (int i=1; i<4; i++) {
		if (compare_card_c(trick[i], trick[bigCardLoc], 1, LoNo) > 0 && follow_suit(trick[i],trick[0].colour))
			bigCardLoc = i;
	}
	return bigCardLoc;
}

int play_trick(int lead, int trump, int missing) {
    //printf("Lead %s\n", playerList[lead].name);
	
    //gather cards
    card_t trick[4];
    for (int i = lead; i < lead+4; i++) {
        if (playerList[i%4].isHuman) {
            //show_stats(i%4);
            //play_card(i%4, get_card(playerList[i%4], trick), lead, trick);
            play_card(i%4, choose_card(playerList[i%4], trick, missing), lead, trick);
        } else {
            play_card(i%4, choose_card(playerList[i%4], trick, missing), lead, trick);
        }
        //printf("%s plays ", playerList[i%4].name);
        //show_card(trick[(i-lead)%4]);
        //printf("\n");
    }
    
    //score cards
    int bigCardLoc = score_trick(trick);
    int newLead = (lead+bigCardLoc)%4;
    playerList[newLead].tricks++;
	reset_trick(trick);
    //printf("%s won\n\n", playerList[newLead].name);
    return newLead;
}

int get_bets(int dealer) {
    int bet = 0;
    betEW = 0;
    betNS = 0;
    //assume 2 tricks from your partner
    for (int i = 0; i < 6; i++) {
        playerList[0].bidList[i] = 2;
        playerList[1].bidList[i] = 2;
        playerList[2].bidList[i] = 2;
        playerList[3].bidList[i] = 2;
    }
    int where = (dealer + 1)%4;
    for (int i = dealer+1; i < dealer+5; i++) {
        int betty = 0;
        if ((i-dealer)%4 == 0 && bet < 6) {
            return stick_dealer(dealer);
        }
        if (playerList[i%4].isHuman) {
            betty = human_bet();
        } else {
            betty = computer_bet();
        }
        if (betty > bet) {
            bet = betty;
            where = i%4;
            printf("%s bet %d\n", playerList[where].name, betty);
        } else {
            printf("%s passes\n", playerList[i%4].name);
        }
    }
	if (where%2 == 0) {
		betEW = bet;
	} else {
		betNS = bet;
	}
	printf("%s won a bet of %d and called ", playerList[where].name, bet); //trump listed later on
	return where;
    return -1; // In case something goes horribly wrong
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
        sort(playerList[i].hand);
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