//
//  ai.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "ai.h"


int choose_bet(player_t player) {
	for (int i=0; i<6; i++) {
		player.bidList[i]=2; // count on 2 tricks from your partner
	}
	for (int i = 0; i < 12; i++) {
		switch (player.hand[i].rank) {
			case NINE:
				player.bidList[0] += 1;
				break;
			case TEN:
				player.bidList[0] += 1;
				break;
			case ACE:
				player.bidList[5] += 1;
				switch (player.hand[i].colour) {
					case CLUBS:
						player.bidList[1]++;
						break;
					case DIAMONDS:
						player.bidList[2]++;
						break;
					case SPADES:
						player.bidList[3]++;
						break;
					case HEARTS:
						player.bidList[4]++;
						break;
						
					default:
						printf("Error in suit");
						break;
				}
				break;
			case KING:
				player.bidList[5] += 2;
				break;
			case JACK:
				switch (player.hand[i].colour) {
					case CLUBS:
						player.bidList[1] += 5;
						player.bidList[3] += 2;
						break;
					case DIAMONDS:
						player.bidList[2] += 5;
						player.bidList[4] += 2;
						break;
					case SPADES:
						player.bidList[3] += 5;
						player.bidList[1] += 2;
						break;
					case HEARTS:
						player.bidList[4] += 5;
						player.bidList[2] += 2;
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
	return 0;
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

int choose_trump(player_t player) {
    int max = 0;
    for (int i = 0; i < 6; i++) {
        if (player.bidList[i] > player.bidList[max]) {
            max = i;
        }
    }
    return max;
}