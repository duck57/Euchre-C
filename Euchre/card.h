//
//  card.h
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

// Functions for dealing with single cards

#ifndef Euchre_card_h
#define Euchre_card_h

#include <stdlib.h>

typedef enum {BLANK, CLUBS, DIAMONDS, SPADES, HEARTS, TRUMP, JOKER} suit_t;
typedef enum {NONE, DEUCE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, LEFT, RIGHT} value_t;

typedef struct card_t {
    suit_t colour;
    value_t rank;
} card_t;

card_t make_card(const suit_t suit, const value_t value);
int compare_card(const void *a, const void *b);
int compare_card_c(const card_t a, const card_t b, const int suitImportant, const int lowWin);
card_t cast_card(const void *a);
int compare_suit(const card_t a, const card_t b);
int compare_rank(const card_t a, const card_t b);


char *show_rank(const value_t value);
char *show_suit(const suit_t colour);
char *display_rank(const value_t value);
char *display_suit(const suit_t colour);

char *print_card(const card_t card, const suit_t trumpSuit);
char *print_card_full(const card_t card);
void show_card(const card_t card, const suit_t trumpSuit);
void show_card_full(const card_t card);

card_t blank_card();
card_t erase_card(card_t *card);
int follow_suit(const card_t card, const suit_t checkSuit, const int isTrumpGame);

card_t to_trump(card_t *card);
card_t revert_card(card_t *card, const suit_t trumpSuit);
card_t make_card_trump(card_t *card, const suit_t trumpSuit);
char * display_trump(const int trump);

int is_blank_card(const card_t card);
int is_not_blank(const card_t card);
int is_suit(const card_t card, const suit_t suit);
int is_not_trump(const card_t card);
int is_trump(const card_t card);
int is_not_suit(const card_t card, const suit_t suit);
int is_rank(const card_t card, const value_t rank);
int is_not_rank(const card_t card, const value_t rank);

card_t change_rank(card_t *card, const value_t newRank);
card_t chagne_suit(card_t *card, const suit_t newSuit);

#endif
