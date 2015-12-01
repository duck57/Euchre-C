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
int repeat();

void setup_player(player_t *player);
void set_name(player_t *player);
void set_AI(player_t *player);

int help(const char *chk);
int getLine (const char *prmpt, char *buff, const size_t sz);
int input(const char *prompt, char *readBuff, const size_t size);
int get_number_in_range(const char *prompt, const int min, const int max, const int digits);

#endif /* menus_h */
