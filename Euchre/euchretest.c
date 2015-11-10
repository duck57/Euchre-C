//
//  euchretest.c
//  Euchre
//
//  Created by Chris Matlak on 3/31/14.
//  Copyright (c) 2014 TimmyJ_NET. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "euchretest.h"
//#include "euchre.h"

int random_trump_2();

void test_euchre() {
    /*for (int i = 0; i < 99; i++) {
        random_trump_2();
    }*/
    printf("\n");
    init_players();
    play_hand((int)(((float)arc4random()/0x100000000)*4));
}



int random_trump_2() {
    int trump = (int)(((float)arc4random()/0x100000000)*6);
    make_euchre_trump(trump);
    printf("Trump is %s\n\n", display_suit((suit_t)trump));
    return trump;
}