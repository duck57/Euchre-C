//
//  bid.c
//  Euchre in C
//
//  Created by Chris Matlak on 11/30/15.
//  Copyright © 2015 Euchre US!. All rights reserved.
//

// this is specifically the methods for generating the bid list
// the bet itself is found in bet.c

#include "bid.h"

/*
 bidList contains a list of guesses of how many tricks can be won in the following format:
 bidList[n] - potential trump call
 0 - Low No
 1 - Clubs
 2 - Diamonds
 3 - Spades
 4 - Hearts
 5 - High No
 
 6 - Index of best call (randomly chosen if a tie)
 */

void generate_bid_list(player_t *computer) {
	// Auto-pick for humans, AI level 2, and AI level -4 all use the strategic trump
	if (mod(computer->AI, 2) == 0)
		calculate_tricks(computer);
	else
		analyse_cards(computer);
	select_best_bet(computer);
}

// bidding based on a strict analysis of the cards
void analyse_cards(player_t *computer) {
	const int rightBst = 5;
	const int leftBst = 2;
	const int noTrumpWin = 4;
	const int aceBst = 2;
	const int noTrumpBst = 2;
	const int suitCnt = 1;
	const int tmpAcePen = 1;
	
	//show_hand(computer); // debugging
	for (int i=0; i<12; i++) {
		switch (computer->hand[i].rank) {
				// Lo No
			case NINE:
				computer->bidList[0] += noTrumpWin;
				break;
			case TEN:
				computer->bidList[0] += noTrumpBst;
				break;
				
				// Hi No or actual suit
			case ACE:
				computer->bidList[5] += noTrumpWin;
				computer->bidList[1] += aceBst;
				computer->bidList[2] += aceBst;
				computer->bidList[3] += aceBst;
				computer->bidList[4] += aceBst;
				switch (computer->hand[i].colour) {
					case CLUBS:
						computer->bidList[1] -= tmpAcePen;
						break;
					case DIAMONDS:
						computer->bidList[2] -= tmpAcePen;
						break;
					case SPADES:
						computer->bidList[3] -= tmpAcePen;
						break;
					case HEARTS:
						computer->bidList[4] -= tmpAcePen;
						break;
						
					default:
						//printf("Error in suit");
						break;
				}
				break;
				
				// Hi No
			case KING:
				computer->bidList[5] += noTrumpBst;
				break;
				
				// Suits
			case JACK:
				switch (computer->hand[i].colour) {
					case CLUBS:
						computer->bidList[1] += rightBst;
						computer->bidList[3] += leftBst;
						break;
					case DIAMONDS:
						computer->bidList[2] += rightBst;
						computer->bidList[4] += leftBst;
						break;
					case SPADES:
						computer->bidList[3] += rightBst;
						computer->bidList[1] += leftBst;
						break;
					case HEARTS:
						computer->bidList[4] += rightBst;
						computer->bidList[2] += leftBst;
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
		
		switch (computer->hand[i].colour) {
			case CLUBS:
				computer->bidList[1] += suitCnt;
				break;
			case DIAMONDS:
				computer->bidList[2] += suitCnt;
				break;
			case SPADES:
				computer->bidList[3] += suitCnt;
				break;
			case HEARTS:
				computer->bidList[4] += suitCnt;
				break;
				
			default:
				//printf("Error in suit");
				break;
		}
	}
	
	// normalize the bidding and write to the main array
	for (int i=0; i<6; i++) {
		computer->bidList[i] = computer->bidList[i]/2 - 3;
	}
}


// commenting out this until later; hard to implement this cleanly in C
// bidding based on calculating the estimated number of tricks to take
void calculate_tricks(player_t *computer) {
	// until this gets better figured out
	analyse_cards(computer);
	return;
	
	
	 // divide by 5 to get the whole number of tricks
	 //
	 //const int partnerAssumed=0; // using the human rule-of-thumb has made the computer player way too aggressive
	 const int partnerAssumed=10; // count on 2 tricks from your partner
	 const int sureTrick = 5;
	 const int likelyTrick = 3;
	 const int possibleTrick = 2;
	 
	 // Same order as bidList for the [6], 9—Right Bower for the [8]
	 int cardTrack[6][8];
	 card_t suitTest_hand[4][12];
	 
	 for (int i=0; i<6; i++) {
		computer->bidList[i] = partnerAssumed;
	 }
	 
	 for (int i=0; i<4; i++) {
		copy_hand(computer->hand, suitTest_hand[i], 12);
	 }
	 hand_to_trump(suitTest_hand[0], 12, CLUBS);
	 hand_to_trump(suitTest_hand[1], 12, DIAMONDS);
	 hand_to_trump(suitTest_hand[2], 12, SPADES);
	 hand_to_trump(suitTest_hand[3], 12, HEARTS);
	 
	 for (int i=0; i<12; i++) {
		
	 }
	 
	 for (int i=0; i<6; i++) {
		computer->bidList[i] = computer->bidList[i]/6;
	 }
}

// pick the best bet (or randomly pick from the top tier if there's a tie)
void select_best_bet(player_t *computer) {
	computer->bidList[6] = -99; // in case there's a tie for some reason, give an obviously bad value
	int maxLoc = 0;
	int maxVal = 0;
	for (int i = 0; i < 6; i++) {
		if (computer->bidList[i] > maxVal) {
			maxLoc = i;
			maxVal = computer->bidList[maxLoc];
		}
	}
	
	// use this to pick between tied values
	maxLoc = 6;
	while (computer->bidList[maxLoc] != maxVal) {
		maxLoc = random_int(5);
	}
	
	computer->bidList[6] = maxLoc;
}