//
//  card.h
//  Euchre
//
//  Created by Chris Matlak on 3/28/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#ifndef Euchre_card_h
#define Euchre_card_h

#include <stdlib.h>

typedef enum {BLANK, CLUBS, DIAMONDS, SPADES, HEARTS, TRUMP, JOKER} suit_t;
typedef enum {NONE, DEUCE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, LEFT, RIGHT} value_t;

typedef struct card_t {
    suit_t colour;
    value_t rank;
} card_t;

card_t make_card(suit_t suit, value_t value);
int compare_card(const void *a, const void *b);
int compare_card_c(const card_t a, const card_t b);
void make_trump(card_t card);
card_t cast_card(const void *a);
int compare_suit(card_t a, card_t b);
int compare_rank(card_t a, card_t b);


char *show_rank(value_t value);
char *show_suit(suit_t colour);
char *display_rank(value_t value);
char *display_suit(suit_t colour);

char *display_card(card_t card);
char *display_card_full(card_t card);
void show_card(card_t card);
void show_card_full(card_t card);

int card_random();

#endif
