#include "unscramble.h"
#include "readdict.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_starts_with(const char *string, const char *start)
{
    int i;
    for (i = 0; string[i] != '\0' && start[i] != '\0'; i++)
        if (string[i] != start[i])
            return 0;
    if (string[i] == '\0' && start[i] != '\0')
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Usage: %s <word> [-d dictionary-file]\n", argv[0]);
        return 1;
    }

    char *word = "";
    char *dictpath = "american-english";
    char *dictdir = "dict/";
    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dict") == 0) && i != argc - 1)
            dictpath = strdup(argv[++i]);
        else if (strcmp(word, "") == 0)
            word = strdup(argv[i]);
    }

    int from_stdin = 0;
    if (strcmp(word, "") == 0)
        from_stdin = 1;

    if (string_starts_with(dictpath, dictdir) == 0)
    {
        char *dictpath_tmp = strdup(dictpath);
        dictpath = malloc(strlen(dictdir) + strlen(dictpath) + 1);
        strcpy(dictpath, dictdir);
        strcat(dictpath, dictpath_tmp);
        free(dictpath_tmp);
    }

    Dict *dict = new_dict();
    if (read_dict(dict, dictpath) != READDICT_SUCCESS)
    {
        printf("Error: failed to read dictionary file\n");
        free(word);
        free(dictpath);
        free_dict(dict);
        return 1;
    }

    Dict *words = unscramble(dict, word);
    for (Dict *current = words->next; current != NULL; current = current->next)
        printf("%s\n", current->word);

    free(word);
    free(dictpath);
    free_dict(dict);
    free_dict(words);

    return 0;
}
