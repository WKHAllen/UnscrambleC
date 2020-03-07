/*
 * Unscramble words
 */

#pragma once
#ifndef UNSCRAMBLE_H
#define UNSCRAMBLE_H

#define UNSCRAMBLE_FALSE 0
#define UNSCRAMBLE_TRUE  1

#include "readdict.h"

void string_erase(char *word, int index);

int check_char(const char *word, char chr);

int check_word(const char *word1, const char *word2);

Dict *unscramble(Dict *dict, char *word);

#endif // UNSCRAMBLE_H
