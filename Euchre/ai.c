//
//  ai.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "ai.h"

/*
 AI CLASSES:
 2 - Looks at hand when betting, keeps track of remaining cards when deciding what to play
 1 - Looks at hand when betting, plays the best card possible
 0 - Human: see humanIO.c
 -1 - random bid, trump, and play (valid card only)
 -2 - random bid & trump, plays lowest valid card
 -3 - random bid & trump, plays highest valid card
 */

int partnerAssumed=0; // using the human rule-of-thumb has made the computer player way too aggressive
//int partnerAssumed=2; // count on 2 tricks from your partner


/*
 bidList contains a list of guesses of how many tricks can be won in the following format:
 bidList[n] - potential trump call
 0 - Low No
 1 - Clubs
 2 - Diamonds
 3 - Spades
 4 - Hearts
 5 - High No
 
 6 - Best call
 */
void generate_bid_list(player_t computer, int computer_location) {
	for (int i=0; i<6; i++) {
		computer.bidList[i]=partnerAssumed;
	}
	//show_hand(computer); // debugging
	for (int i=0; i<12; i++) {
		switch (computer.hand[i].rank) {
			case NINE:
				computer.bidList[0] += 2;
				break;
			case TEN:
				computer.bidList[0] += 1;
				break;
			case ACE:
				computer.bidList[5] += 2;
				switch (computer.hand[i].colour) {
					case CLUBS:
						computer.bidList[1] += 1;
						break;
					case DIAMONDS:
						computer.bidList[2] += 1;
						break;
					case SPADES:
						computer.bidList[3] += 1;
						break;
					case HEARTS:
						computer.bidList[4] += 1;
						break;
					default:
						printf("Error in suit");
						break;
				}
				break;
			case KING:
				computer.bidList[5] += 1;
				break;
			case JACK:
				switch (computer.hand[i].colour) {
					case CLUBS:
						computer.bidList[1] += 4;
						computer.bidList[3] += 2;
						break;
					case DIAMONDS:
						computer.bidList[2] += 4;
						computer.bidList[4] += 2;
						break;
					case SPADES:
						computer.bidList[3] += 4;
						computer.bidList[1] += 2;
						break;
					case HEARTS:
						computer.bidList[4] += 4;
						computer.bidList[2] += 2;
						break;
					default:
						printf("Error in suit");
						break;
				}
				break;
			default:
				//printf("Error in value");
				break;
		}
	}
	int max = 0;
	for (int i = 0; i < 6; i++) {
		playerList[computer_location].bidList[i]=computer.bidList[i];
		if (computer.bidList[i] > computer.bidList[max])
			max = i;
	}
	computer.bidList[6]=max;
	playerList[computer_location].bidList[6]=max;
}

int choose_bet(player_t computer, int currentHibet) {
	int testBet = computer.bidList[computer.bidList[6]];
	if (testBet>13)
		return 24; // call a loner
	if (testBet==13)
		return 20; // call a shooter
	if (currentHibet==0) {
		if (testBet<9) {
			return testBet; // safe to call 6, 7, or 8 if you're the first bet
		} else if (testBet==13) {
			return 20; // call a shooter
		} else if (testBet>12) {
			return 24; // call a loner
		} else {
			return 5+testBet/2; // don't want to be too aggressive on the first go
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
	printf("\n");
}

int choose_card(player_t computer) {
    //make dummy AI
	
    //choose a card valid to play (follow suit)
    //do not beat partner
    //play trump if not won
    //play low card
    //show_hand(computer);
    while (1) {
        int loc = (((float)arc4random()/0x100000000)*(12-trickNumber));
        if (is_valid_card(computer.hand, computer.hand[loc])) {
            //printf("%s plays (position %d) ", computer.name, loc);
            //show_card(computer.hand[loc]);
            return loc;
        }
        //show_card(computer.hand[loc]);
    }
    printf("\n");
	
    return 0;
}

int choose_trump(player_t computer) {
	return computer.bidList[6];
}