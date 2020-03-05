#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unscramble.h"
#include "readdict.h"

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

    printf("Word:       %s\n", word);
    printf("Dictionary: %s\n", dictpath);
    // TODO: unscramble

    free(word);
    free(dictpath);

    return 0;
}
