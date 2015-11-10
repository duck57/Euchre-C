//
//  ai.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include "ai.h"

int random_bet();
int random_trump();

int human_bet() {
    return random_bet();
}
int computer_bet() {
    return random_bet();
}

int get_card(player_t human, card_t trick[]) {
    //get person to pick card's index to play and remove it
    return 0;
    //return choose_card(human, trick);
}

int choose_card(player_t computer, card_t trick[], int tricksPlayed) {
    //make dummy AI
    
    //choose a card valid to play (follow suit)
    //do not beat partner
    //play trump if not won
    //play low card
    //show_hand(computer);
    while (1) {
        int loc = (((float)arc4random()/0x100000000)*(12-tricksPlayed));
        if (is_valid_card(computer.hand, computer.hand[loc], trick)) {
            //printf("%s plays (position %d) ", computer.name, loc);
            //show_card(computer.hand[loc]);
            return loc;
        }
        //show_card(computer.hand[loc]);
    }
    printf("\n");
    
    return 0;
}

int random_bet() {
    return card_random();
}

int is_valid_card(card_t hand[], card_t test, card_t trick[]) {
    if (test.colour == BLANK || test.rank == NONE)
        return 0;
    if (trick[0].colour == BLANK || trick[0].rank == NONE)
        return 1;
    if (test.colour == trick[0].colour)
        return 1;
    for (int i = 0; i < 12; i++) {
        if (hand[i].colour == trick[0].colour)
            return 0;
    }
    
    return 1;
}

int get_trump(player_t hLead) {
    return choose_trump(hLead);
}

int choose_trump(player_t cLead) {
    for (int i = 0; i < 12; i++) {
        switch (cLead.hand[i].rank) {
            case NINE:
                cLead.bidList[0] += 1;
                break;
            case TEN:
                cLead.bidList[0] += 1;
                break;
            case ACE:
                cLead.bidList[5] += 1;
                switch (cLead.hand[i].colour) {
                    case CLUBS:
                        cLead.bidList[1]++;
                        break;
                    case DIAMONDS:
                        cLead.bidList[2]++;
                        break;
                    case SPADES:
                        cLead.bidList[3]++;
                        break;
                    case HEARTS:
                        cLead.bidList[4]++;
                        break;
                        
                    default:
                        printf("Error in suit");
                        break;
                }
                break;
            case KING:
                cLead.bidList[5] += 2;
                break;
            case JACK:
                switch (cLead.hand[i].colour) {
                    case CLUBS:
                        cLead.bidList[1] += 5;
                        cLead.bidList[3] += 2;
                        break;
                    case DIAMONDS:
                        cLead.bidList[2] += 5;
                        cLead.bidList[4] += 2;
                        break;
                    case SPADES:
                        cLead.bidList[3] += 5;
                        cLead.bidList[1] += 2;
                        break;
                    case HEARTS:
                        cLead.bidList[4] += 5;
                        cLead.bidList[2] += 2;
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
        if (cLead.bidList[i] > cLead.bidList[max]) {
            max = i;
        }
    }
    return max;
}

int random_trump() {
    int trump = (int)(((float)arc4random()/0x100000000)*6);
    make_euchre_trump(trump);
    printf("Trump is %s\n\n", display_suit((suit_t)trump));
    return trump;
}