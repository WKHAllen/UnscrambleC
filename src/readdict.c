#include "readdict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(FILE *fp, char *line, int max)
{
    if (fgets(line, max, fp) == NULL)
        return 0;
    else
    {
        int linelen = strlen(line);
        line[linelen - 1] = '\0';
        return linelen - 1;
    }
}

Dict *new_dict()
{
    Dict *dict = malloc(sizeof(dict));
    dict->word = "";
    dict->next = NULL;
    dict->size = 0;
    return dict;
}

int read_dict(Dict *dict, const char *dictpath)
{
    Dict *current = dict;
    char buffer[MAX_LINE_LEN];

    FILE *fp = fopen(dictpath, "r");
    if (fp == NULL)
        return READDICT_OPEN_FILE_ERROR;

    int linelen = 1;
    while ((linelen = get_line(fp, buffer, MAX_LINE_LEN)) > 0)
    {
        Dict *new_node = malloc(sizeof(new_node));
        char *new_word = malloc((linelen + 1) * sizeof(char));
        strcpy(new_word, buffer);
        new_node->word = new_word;
        current->next = new_node;
        current = new_node;
        dict->size++;
    }

    if (fclose(fp) != 0)
        return READDICT_CLOSE_FILE_ERROR;

    return READDICT_SUCCESS;
}

void free_dict(Dict *dict)
{
    Dict *next = dict->next;

    while (next != NULL)
    {
        free(dict->word);
        free(dict);
        dict = next;
        next = dict->next;
    }
}
