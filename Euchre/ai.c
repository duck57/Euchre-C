//
//  ai.c
//  Euchre
//
//  Created by Chris J.M. on 3/31/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include "ai.h"

/*
 AI CLASSES:
 2 - Looks at hand when betting, keeps track of remaining cards when deciding what to play
 1 - Looks at hand when betting, plays the best card possible
 0 - Human: see humanIO.c
 -1 - random bid, trump, and card (valid card only)
 -2 - random bid & trump, plays best card
 -3 - random bid & trump, plays highest valid card
 -4 - random bid, but selects the best trump and card
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
	h(0.123);
	if (computer.AI<0)
		return random_euchre_bet();
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
	h(0.111);
	int validCardAry[13];
	sort_hand(computer.hand, 12-trickNumber);
	get_valid_cards(computer.hand, validCardAry);
	switch (computer.AI) {
		case -1:
			return play_random_card(computer);
			break;
		case -3:
			return play_random_card(computer);
			break;
		default:
			return play_random_card(computer);
			break;
	}
	return -4;
}

void get_valid_cards(card_t hand[], int validCardAry[]) {
	int count=0;
	for (int i=0; i<12-trickNumber; i++) {
		if (is_valid_card(hand, hand[i])) {
			validCardAry[count]=i;
			count++;
		}
	}
}

int play_random_card(player_t computer) {
	while (1) {
		int loc = random_int(12-trickNumber);
		if (is_valid_card(computer.hand, computer.hand[loc]))
			return loc;
	}
	return -25;
}

int choose_trump(player_t computer) {
	h(0.099);
	return (computer.AI>0||computer.AI==-4) ? computer.bidList[6] : random_bidEuchre_trump();
}

int random_euchre_bet() {
	int r = random_int(999);
	if (r < 585)
		return 0;
	if (r < 864)
		return 6;
	if (r < 911)
		return 7;
	if (r < 941)
		return 8;
	if (r < 963)
		return 9;
	if (r < 984)
		return 10;
	if (r < 998)
		return 11;
	return 12;
}

int random_bidEuchre_trump() {
	return random_int(6);
}