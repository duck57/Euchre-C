//
//  card.c
//  Euchre
//
//  Created by Chris J.M. on 3/28/14.
//  Copyright (c) 2014 Euchre US!. 2-clause BSD.
//

#include <stdio.h>
#include "card.h"

card_t make_card(suit_t suit, value_t value) {
    card_t temp = {suit, value};
    return temp;
}

char *display_card(card_t card) {
    char *test = "";
    sprintf(test, "%s%s", show_rank(card.rank), show_suit(card.colour));
    return test;
}

void show_card(card_t card) {
    printf("%s%s ", show_rank(card.rank), show_suit(card.colour));
}

void show_card_full(card_t card) {
    printf("%s of %s ", display_rank(card.rank), display_suit(card.colour));
}

char *display_card_full(card_t card) {
    char *temp = "";
    sprintf(temp, "%s of %s", display_rank(card.rank), display_suit(card.colour));
    return temp;
}

// Use this comparison for sort operators to group cards by suit in your hand
int compare_card(const void *a, const void *b) {
    card_t ad = *(card_t*)a;
    card_t bd = *(card_t*)b;
	int s = ad.colour - bd.colour;
    int r = ad.rank - bd.rank;
    if (s == 0)
        return r;
    else
        return s;
	return 420;
}

/* returns the difference (card a - card b)
	positive values mean card a won; b wins if this returns a negative value */
int compare_card_c(const card_t a, const card_t b, int trumpGame, int LoWin) {
	int s = 0;
	if (trumpGame)
		s = a.colour - b.colour; // compare suit first for trump-based games
    int r = a.rank - b.rank;
	if (LoWin)
		r = -r;
    if (s == 0)
        return r;
    else
        return s;
	return -420; // this should never happen
}

/*	Returns if a card is following a certain suit
	Trump is assumed to follow suit at all times*/
int follow_suit(const card_t card, const suit_t checkSuit) {
	if (card.colour == checkSuit || card.colour == TRUMP)
		return 1;
	else
		return 0;
	return 899;
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


char *show_rank(value_t value) {
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
            return "Ⅹ";
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
char *show_suit(suit_t colour) {
    switch (colour) {
        case JOKER:
            return "🃏";
            break;
        case HEARTS:
            return "♥";
            break;
        case SPADES:
            return "♠";
            break;
        case DIAMONDS:
            return "♦︎";
            break;
        case CLUBS:
            return "♣︎";
            break;
        case TRUMP:
            return "✯";
            break;
        case BLANK:
            return " ";
            break;
            
        default:
            return "❂";
            break;
    }
}
char *display_rank(value_t value) {
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
char *display_suit(suit_t colour) {
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

void make_trump(card_t card) {
    card.colour = TRUMP;
}

void sort_hand(card_t hand[], int numberOfCards) {
	int cardSize = sizeof(card_t);
	qsort(hand, numberOfCards, cardSize, compare_card);
}

card_t blank_card() {
	return make_card(BLANK, NONE);
}

void revert_card(card_t card, suit_t trumpSuit) {
	if (card.colour == TRUMP)
		card.colour = trumpSuit;
}

void make_card_trump(card_t card, suit_t trump) {
	if (card.colour == trump) {
		card.colour = TRUMP;
		if (card.rank == JACK)
			card.rank = RIGHT;
	} else if (card.rank == JACK) {
		switch (trump) {
			case 1:
				if (card.colour == SPADES) {
					card.colour = TRUMP;
					card.rank = LEFT;
				}
				break;
			case 2:
				if (card.colour == HEARTS) {
					card.colour = TRUMP;
					card.rank = LEFT;
				}
				break;
			case 3:
				if (card.colour == CLUBS) {
					card.colour = TRUMP;
					card.rank = LEFT;
				}
				break;
			case 4:
				if (card.colour == DIAMONDS) {
					card.colour = TRUMP;
					card.rank = LEFT;
				}
				break;
				
			default:
				
				break;
		}
	}
}

char * display_trump(int trump) {
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