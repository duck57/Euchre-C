//
//  card.c
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include <stdio.h>
#include "card.h"

card_t make_card(const suit_t suit, const value_t value) {
    card_t temp = {suit, value};
    return temp;
}

char *print_card(const card_t card, const suit_t trumpSuit) {
    char *test = malloc(sizeof(char[2]));
	suit_t outSuit = card.colour;
	value_t dspVal = card.rank;
	if (card.colour == TRUMP) {
		outSuit = trumpSuit;
		if (card.rank == LEFT || card.rank == RIGHT)
			dspVal = JACK;
		if (card.rank == LEFT) {
			switch (trumpSuit) {
				case CLUBS:
					outSuit = SPADES;
					break;
				case DIAMONDS:
					outSuit = HEARTS;
					break;
				case SPADES:
					outSuit = CLUBS;
					break;
				case HEARTS:
					outSuit = DIAMONDS;
					break;
					
				default:
					break;
			}
		}
	}
    sprintf(test, "%s%s", show_rank(dspVal), show_suit(outSuit));
    return test;
}

void show_card(const card_t card, const suit_t trumpSuit) {
    printf("%s", print_card(card, trumpSuit));
}

char *print_card_full(const card_t card) {
	char *temp = malloc(44*sizeof(char));
	switch (card.rank) {
		case LEFT:
			sprintf(temp, "Left Bower");
			break;
		case RIGHT:
			sprintf(temp, "Right Bower");
			
		default:
			sprintf(temp, "%s of %s", display_rank(card.rank), display_suit(card.colour));
			break;
	}
	return temp;
}

void show_card_full(const card_t card) {
    printf("%s ", print_card_full(card));
}

// Use this comparison for sort operators to group cards by suit in your hand
int compare_card(const void *a, const void *b) {
    card_t ad = *(card_t*)a;
    card_t bd = *(card_t*)b;
	int s = ad.colour - bd.colour;
    int r = ad.rank - bd.rank;
	return s == 0 ? r : s;
}

/* returns the difference (card a - card b)
	positive values mean card a won; b wins if this returns a negative value */
int compare_card_c(const card_t a, const card_t b, const int suitImportant, const int LoWin) {
	int s = 0;
	if (suitImportant)
		s = a.colour - b.colour; // compare suit first for trump-based games
    int r = a.rank - b.rank;
	if (LoWin)
		r = -r;
	return s == 0 ? r : s;
}

/*	Returns if a card is following a certain suit
	Trump is assumed to follow suit at all times
 	Doesn't care about what other cards you have in your hand
 */
int follow_suit(const card_t card, const suit_t checkSuit, const int isTrumpGame) {
	return (is_suit(card, checkSuit) || (is_trump(card) && isTrumpGame)) ? 1 : 0;
}

int compare_suit(const card_t a, const card_t b) {
    return a.colour - b.colour;
}

int compare_rank(const card_t a, const card_t b) {
    return a.rank - b.rank;
}

card_t cast_card(const void *a) {
    card_t *pa = (struct card_t*) a;
    return make_card(pa->colour,pa->rank);
}


char *show_rank(const value_t value) {
    switch (value) {
        case NONE:
            return " ";
            break;
        case DEUCE:
            return "𝟚";
            break;
        case TWO:
            return "2";
            break;
        case THREE:
            return "3";
            break;
        case FOUR:
            return "4";
            break;
        case FIVE:
            return "5";
            break;
        case SIX:
            return "6";
            break;
        case SEVEN:
            return "7";
            break;
        case EIGHT:
            return "8";
            break;
        case NINE:
            return "9";
            break;
        case TEN:
            return "⒑";
            break;
        case JACK:
            return "J";
            break;
        case QUEEN:
            return "Q";
            break;
        case KING:
            return "K";
            break;
        case ACE:
            return "A";
            break;
        case LEFT:
            return "◀";
            break;
        case RIGHT:
            return "▶";
            break;
            
        default:
            return "?";
            break;
    }
}

char *show_suit(const suit_t colour) {
    switch (colour) {
        case JOKER:
            return "🃏";
            break;
        case HEARTS:
            return "♥️";
            break;
        case SPADES:
            return "♠️";
            break;
        case DIAMONDS:
            return "♦️";
            break;
        case CLUBS:
            return "♣️";
            break;
        case TRUMP:
            return "🌟";
            break;
        case BLANK:
            return " ";
            break;
            
        default:
            return "❂";
            break;
    }
}

char *display_rank(const value_t value) {
    switch (value) {
        case NONE:
            return "";
            break;
        case DEUCE:
            return "Deuce";
            break;
        case TWO:
            return "Two";
            break;
        case THREE:
            return "Three";
            break;
        case FOUR:
            return "Four";
            break;
        case FIVE:
            return "Five";
            break;
        case SIX:
            return "Six";
            break;
        case SEVEN:
            return "Seven";
            break;
        case EIGHT:
            return "Eight";
            break;
        case NINE:
            return "Nine";
            break;
        case TEN:
            return "Ten";
            break;
        case JACK:
            return "Jack";
            break;
        case QUEEN:
            return "Queen";
            break;
        case KING:
            return "King";
            break;
        case ACE:
            return "Ace";
            break;
        case LEFT:
            return "Left";
            break;
        case RIGHT:
            return "Right";
            break;
            
        default:
            return "extra";
            break;
    }
}

char *display_suit(const suit_t colour) {
    switch (colour) {
        case JOKER:
            return "Joker";
            break;
        case HEARTS:
            return "Hearts";
            break;
        case SPADES:
            return "Spades";
            break;
        case DIAMONDS:
            return "Diamonds";
            break;
        case CLUBS:
            return "Clubs";
            break;
        case TRUMP:
            return "Trump";
            break;
        case BLANK:
            return "";
            break;
            
        default:
            return "error";
            break;
    }
}

card_t change_rank(card_t *card, const value_t newRank) {
	card->rank = newRank;
	return *card;
}

card_t change_suit(card_t *card, const suit_t newSuit) {
	card->colour = newSuit;
	return *card;
}

// simply changes the suit, used for display and human-usable sorting
card_t to_trump(card_t *card) {
	change_suit(card, TRUMP);
	return *card;
}

card_t blank_card() {
	return make_card(BLANK, NONE);
}

card_t erase_card(card_t *card) {
	*card = blank_card();
	return *card;
}

// keep the left & right as left & right instead of jacks (for human-sorted display)
card_t revert_card(card_t *card, const suit_t trumpSuit) {
	if (is_trump(*card))
		change_suit(card, trumpSuit);
	return *card;
}

card_t make_card_trump(card_t *card, const suit_t trumpSuit) {
	if (is_suit(*card, trumpSuit)) {
		to_trump(card);
		if (is_rank(*card, JACK))
			change_rank(card, RIGHT);
	} else if (is_rank(*card, JACK)) {
		switch (trumpSuit) {
			case CLUBS:
				if (is_suit(*card, SPADES)) {
					to_trump(card);
					change_rank(card, LEFT);
				}
				break;
			case DIAMONDS:
				if (is_suit(*card, HEARTS)) {
					to_trump(card);
					change_rank(card, LEFT);
				}
				break;
			case SPADES:
				if (is_suit(*card, CLUBS)) {
					to_trump(card);
					change_rank(card, LEFT);
				}
				break;
			case HEARTS:
				if (is_suit(*card, DIAMONDS)) {
					to_trump(card);
					change_rank(card, LEFT);
				}
				break;
				
			default:
				
				break;
		}
	}
	
	return *card;
}

char * display_trump(const int trump) {
	char *trumpDisp;
	if (trump == 0) {
		trumpDisp = "LoNo";
	} else if (trump == 5) {
		trumpDisp = "HiNo";
	} else {
		trumpDisp = display_suit((suit_t) trump);
	}
	return trumpDisp;
}

int is_blank_card(const card_t card) {
	return compare_card_c(card, blank_card(), 1, 0);
}

int is_not_blank(const card_t card) {
	return !is_blank_card(card);
}

int is_not_trump(const card_t card) {
	return is_not_suit(card, TRUMP);
}

int is_trump(const card_t card) {
	return is_suit(card, TRUMP);
}

int is_not_suit(const card_t card, const suit_t suit) {
	return !is_suit(card, suit);
}

int is_suit(const card_t card, const suit_t suit) {
	return card.colour == suit;
}

int is_rank(const card_t card, const value_t rank) {
	return card.rank == rank;
}

int is_not_rank(const card_t card, const value_t rank) {
	return !is_rank(card, rank);
}