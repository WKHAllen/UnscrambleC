/*
 * Read dictionary files
 */

#pragma once
#ifndef READDICT_H
#define READDICT_H

#define READDICT_SUCCESS          0
#define READDICT_OPEN_FILE_ERROR  1
#define READDICT_CLOSE_FILE_ERROR 2

#define MAX_LINE_LEN 64

#include <stdio.h>
#include <stddef.h>

typedef struct dictnode
{
    char *word;
    struct dictnode *next;
    size_t size;
} Dict;

int get_line(FILE *fp, char *line, int max);

Dict *new_dict(void);

void dict_set_next_word(Dict *node, char *word);

int read_dict(Dict *dict, const char *dictpath);

void free_dict(Dict *dict);

#endif // READDICT_H
