//
//  mathemagics.c
//  Euchre
//
//  Created by Chris Matlak on 11/19/15.
//  Copyright © 2015 TimmyJ_NET. All rights reserved.
//

#include "mathemagics.h"


int mod(int a, int b) {
	int r = a % b;
	return r < 0 ? r + b : r;
}

bool is_valid_int(const char *str) {
	// Handle negative numbers.
	//
	if (*str == '-')
		++str;
	
	// Handle empty string or just "-".
	//
	if (!*str)
		return false;
	
	// Check for non-digit chars in the rest of the stirng.
	//
	while (*str) {
		if (!isdigit(*str))
			return false;
		else
			++str;
	}
	
	return true;
}

bool is_exponent_char(const char test) {
	return (isdigit(test) || test == '-' || test == '+') ? true : false;
}

bool is_valid_number(const char *str) {
	int commaSpace = 0;
	bool hasDecimal = false;
	const int commaSpacing = 3;
	bool hasComma = false;
	bool hasExponent= false;
	
	// Handle negative numbers.
	if (*str == '-')
		++str;
	
	// Handle empty string or just "-".
	if (!*str)
		return false;
	
	// Check for non-digit chars in the rest of the stirng.
	//
	while (*str) {
		// Deal with thousands separators
		if (*str == ',') {
			if (hasDecimal || hasExponent)
				return false; // No commas after the decimal point or exponent
			if (hasComma==false) {
				if (commaSpace>commaSpacing)
					return false; // Use commas right or not at all!
				hasComma=true;
			}
			commaSpace = 0;
			++str;
		}
		if (*str == '.') {
			if (hasDecimal || hasExponent)
				return false;
			hasDecimal = true;
			++str;
		}
		if (*str == 'e' || *str == 'E') {
			if (hasExponent || hasComma)
				return false; // no stacked exponents or mixed commas and exponents
			hasExponent = true;
			++str;
			if (!*str)
				return false;
			if (*str == '+')
				++str;
			return is_valid_int(str); // str should be an int by now
		}
		if (!hasDecimal)
			commaSpace++;
		if (!isnumber(*str))
			return false;
		else
			++str;
	}
	return (hasComma && commaSpace!=commaSpacing) ? false : true;
}

// Assumes it's already been validated, but also allows for arbitrary commas
int to_int (const char *str) {
	int out = 0;
	bool negative = false;
	while (*str) {
		out *= 10;
		if (*str == '-') {
			negative = true;
			++str;
		}
		if (*str == ',')
			++str;
		out += *str - 48; // Hopefully hard-coding ASCII won't bite me
		++str;
	}
	return negative ? -out : out;
}

// Assumes it's already been validated, and doesn't care about comma placement
// Doesn't currently work with exponents in the number, but that's not needed for Euchre
double to_double (const char *str) {
	double out = 0;
	bool negative = false;
	int exponent = 0;
	bool hasDecimal = false;
	char temp[sizeof(str)];
	int track = 0;
	
	while (*str) {
		out *= 10.0;
		if (*str == '-') {
			negative = true;
			++str;
		}
		if (*str == ',')
			++str;
		if (*str == '.') {
			hasDecimal = true;
			++str;
		}
		if (hasDecimal)
			track++;
		if (*str == 'e' || *str == 'E') {
			++str;
			while (*str) {
				temp[exponent] = *str;
				++str;
			}
			out *= pow(10.0,to_int(temp)-track);
			return negative ? -out : out;
		}
		out += (*str - 48); // Hopefully hard-coding ASCII won't bite me
		++str;
	}
	out *= pow(10,-track);
	return negative ? -out : out;
}

int power(int base, unsigned int exp) {
	int i, result = 1;
	for (i = 0; i < exp; i++)
		result *= base;
	return result;
}