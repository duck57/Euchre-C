//
//  menus.h
//  Euchre
//
//  Created by Chris J.M. on 11/18/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef menus_h
#define menus_h

#include <stdio.h>
#include <string.h>
#include "initZero.h"
#include "help.h"
#include "mathemagics.h"

int UNINIT;
int HELP;
int NOTHING;
int ENTERED;
int OVER;
int OUT;
int ERROR;

void greet();
void set_players();
void setup_player(int playerNumber);
int help(char *chk);
void get_name(int playerNumber);
void set_AI(int playerNumber);

int getLine (char *prmpt, char *buff, size_t sz);
int input(char *prompt, char *readBuff, size_t size);
int get_number_in_range(char *prompt, int min, int max, int digits);

#endif /* menus_h */
