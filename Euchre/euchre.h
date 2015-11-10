//
//  euchre.h
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_euchre_h
#define Euchre_euchre_h

#include <string.h>
#include "shuffle.h"
#include "card.h"

typedef struct player_t {
    card_t hand[12];
    char *name;
    int isHuman;
    int tricks;
    int bet;
    int bidList[6];
} player_t;


player_t playerList[4];
card_t euchreDeck[48];
//card_t trick[4];



void deal();
int score_in_range();
void sort(card_t hand[]);
void clear_hand();

void shuffle_deck();
void make_euchre_deck(card_t euchreDeck[]);
void make_double_euchre_deck(card_t euchreDeck[]);

void show_hand(player_t player);
void show_stats(int player);

void zero_players();
void init_players();

void play_euchre();
void play_hand(int dealer);
int play_trick(int lead, int trump, int missing);
void play_card(int player, int cardLoc, int lead, card_t trick[]);

int get_bets(int dealer);
int make_euchre_trump(int trump);
int stick_dealer(int dealer);
int follow_suit(const card_t card, const suit_t checkSuit);


#endif