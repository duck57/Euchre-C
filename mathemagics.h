//
//  mathemagics.h
//  Euchre
//
//  Created by Chris J.M. on 11/19/15.
//  Copyright © 2015 Euchre US!. 2-clause BSD.
//

#ifndef mathemagics_h
#define mathemagics_h

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int mod(int a, int b);
bool is_valid_int(const char *str);
bool is_valid_number(const char *str);
bool is_exponent_char(const char test);
int power(int base, unsigned int exp);
int to_int(const char *str);
double to_double(const char *str);
void pad_zero(char *out, int number, int length);
int random_int(int max);
int random_float(double max);

#endif /* mathemagics_h */
