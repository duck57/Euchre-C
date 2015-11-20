//
//  menus.h
//  Euchre
//
//  Created by Chris Matlak on 11/18/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#ifndef menus_h
#define menus_h

#include <stdio.h>
#include <string.h>
#include "initZero.h"
#include "help.h"
#include "mathemagics.h"

void greet();
void set_players();
void setup_player(int playerNumber);
int help(char *chk);
void get_name(int playerNumber);
void set_AI(int playerNumber);

#endif /* menus_h */
