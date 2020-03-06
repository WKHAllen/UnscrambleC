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

    if (strcmp(word, "") == 0)
    {
        printf("Error: no word given\n");
        free(word);
        free(dictpath);
        return 1;
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

    // Test that the dictionary was created
    Dict *current = dict->next;
    for (int i = 0; i < 10 && current != NULL; i++)
    {
        printf("%s\n", current->word);
        current = current->next;
    }

    free(word);
    free(dictpath);
    free_dict(dict);

    printf("Done\n");

    return 0;
}
