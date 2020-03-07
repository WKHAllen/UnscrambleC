#include "unscramble.h"
#include "readdict.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Usage: %s <word> [-d dictionary-file]\n", argv[0]);
        return 1;
    }

    char *word = "";
    char *dictpath = "dict/american-english";
    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dict") == 0) && i != argc - 1)
        {
            dictpath = (char *)malloc(sizeof(argv[i + 1]));
            strcpy(dictpath, argv[i + 1]);
            i++;
        }
        else if (strcmp(word, "") == 0)
        {
            word = (char *)malloc(sizeof(argv[i]));
            strcpy(word, argv[i]);
        }
    }

    int from_stdin = 0;
    if (strcmp(word, "") == 0)
        from_stdin = 1;

    Dict *dict = new_dict();
    if (read_dict(dict, dictpath) != READDICT_SUCCESS)
    {
        printf("Error: failed to read dictionary file\n");
        if (from_stdin == 0)
            free(word);
        free(dictpath);
        free_dict(dict);
        return 1;
    }

    Dict *words = unscramble(dict, word);
    Dict *current = words->next;
    while (current != NULL)
    {
        printf("%s\n", current->word);
        current = current->next;
    }

    free(word);
    free(dictpath);
    free_dict(dict);
    free_dict(words);

    return 0;
}
