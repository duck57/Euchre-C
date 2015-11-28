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
 2 - Calculates number of guaranteed tricks for bet, keeps track of remaining cards when deciding what to play, bets strategically
 1 - Simple look at hand when betting, plays the best card possible (while trying not to beat partner)
 0 - Human: see humanIO.c
 -1 - random bid, trump, and card (valid card only)
 -2 - random bid & trump, plays best card
 -3 - random bid & trump, plays highest valid card
 -4 - random bid, but selects the best trump and card
 */

//int partnerAssumed=0; // using the human rule-of-thumb has made the computer player way too aggressive
int partnerAssumed=2; // count on 2 tricks from your partner


// TODO: better bidding, based on analysing tricks (needs trump-making and sorting to work first)
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
    const int rightBst = 5;
    const int leftBst = 2;
    const int noTrumpWin = 4;
    const int aceBst = 2;
    const int noTrumpBst = 2;
    const int suitCnt = 1;
    const int tmpAcePen = 1;
    
	//show_hand(computer); // debugging
	for (int i=0; i<12; i++) {
		switch (computer.hand[i].rank) {
				// Lo No
			case NINE:
				computer.bidList[0] += noTrumpWin;
				break;
			case TEN:
				computer.bidList[0] += noTrumpBst;
				break;
				
				// Hi No or actual suit
			case ACE:
				computer.bidList[5] += noTrumpWin;
                computer.bidList[1] += aceBst;
                computer.bidList[2] += aceBst;
                computer.bidList[3] += aceBst;
                computer.bidList[4] += aceBst;
				switch (computer.hand[i].colour) {
					case CLUBS:
						computer.bidList[1] -= tmpAcePen;
						break;
					case DIAMONDS:
						computer.bidList[2] -= tmpAcePen;
						break;
					case SPADES:
						computer.bidList[3] -= tmpAcePen;
						break;
					case HEARTS:
						computer.bidList[4] -= tmpAcePen;
						break;
                        
					default:
						//printf("Error in suit");
						break;
				}
				break;
				
				// Hi No
			case KING:
				computer.bidList[5] += noTrumpBst;
				break;
				
				// Suits
			case JACK:
				switch (computer.hand[i].colour) {
					case CLUBS:
						computer.bidList[1] += rightBst;
						computer.bidList[3] += leftBst;
						break;
					case DIAMONDS:
						computer.bidList[2] += rightBst;
						computer.bidList[4] += leftBst;
						break;
					case SPADES:
						computer.bidList[3] += rightBst;
						computer.bidList[1] += leftBst;
						break;
					case HEARTS:
						computer.bidList[4] += rightBst;
						computer.bidList[2] += leftBst;
						break;
						
					default:
						//printf("Error in suit");
						break;
				}
				break;
                
				
			default:
				//printf("Error in value");
				break;
		}
        
        switch (computer.hand[i].colour) {
            case CLUBS:
                computer.bidList[1] += suitCnt;
                break;
            case DIAMONDS:
                computer.bidList[2] += suitCnt;
                break;
            case SPADES:
                computer.bidList[3] += suitCnt;
                break;
            case HEARTS:
                computer.bidList[4] += suitCnt;
                break;
                
            default:
                //printf("Error in suit");
                break;
        }
	}
    
    
    // pick the best bet (or randomly choose if two are tied)
	int maxLoc = 0;
	int maxVal = 0;
	for (int i = 0; i < 6; i++) {
        computer.bidList[i] = computer.bidList[i]/2-3; // normalize the bidding
		playerList[computer_location].bidList[i] = computer.bidList[i];
		if (computer.bidList[i] > maxVal) {
			maxLoc = i;
			maxVal = computer.bidList[maxLoc];
		}
	}
	
	// use this to pick between tied values
	maxLoc = 6;
	while (computer.bidList[maxLoc] != maxVal) {
		maxLoc = random_int(5);
	}
	
	computer.bidList[6] = maxLoc;
	playerList[computer_location].bidList[6] = maxLoc;
}

// This assumes the bidding has already been normalized
int choose_bet(player_t computer, int currentHibet) {
	h(0.123 * sec);
	
	if (computer.AI<0)
		return random_euchre_bet();
    
    printf("\t"); print_bids(computer); printf("\t%d\t", computer.bidList[6]);
    
    int testBet = computer.bidList[computer.bidList[6]];
	if (testBet < 6)
		return 0;
	if (testBet>13)
		return 24; // call a loner
	if (testBet==13)
		return 20; // call a shooter
	if (currentHibet==0) {
		if (testBet<9) {
			return testBet; // safe to call 6, 7, or 8 if you're the first bet
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
}

int choose_card(player_t computer) {
	h(0.111 * sec);
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
	h(0.099 * sec);
	return (computer.AI>0||computer.AI==-4) ? computer.bidList[6] : random_bidEuchre_trump();
}

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

int random_bidEuchre_trump() {
	return random_int(6);
}