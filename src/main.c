#include "unscramble.h"
#include "readdict.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

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

int input(char *prompt, char **string)
{
    *string = NULL;
    size_t size;
    printf("%s", prompt);
    return getline(string, &size, stdin);
}

int main(int argc, char **argv)
{
    char *word = "";
    char *dictpath = "american-english";
    char *dictdir = "dict/";
    for (int i = 1; i < argc; i++)
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dict") == 0) && i != argc - 1)
            dictpath = strdup(argv[++i]);
        else if (strcmp(word, "") == 0)
            word = strdup(argv[i]);

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

    Dict *words;
    int words_init = 0;
    if (from_stdin == 0)
    {
        words = unscramble(dict, word);
        words_init = 1;
        for (Dict *current = words->next; current != NULL; current = current->next)
            printf("%s\n", current->word);
    }
    else
    {
        int linelen = input("> ", &word);
        if (linelen == -1)
        {
            free(word);
            free(dictpath);
            free_dict(dict);
            printf("Error: failed to read input from stdin\n");
            return 1;
        }
        else if (linelen > 0)
            word[linelen - 1] = '\0';

        while (word[0] != '\0')
        {
            words = unscramble(dict, word);
            words_init = 1;
            for (Dict *current = words->next; current != NULL; current = current->next)
                printf("  | %s\n", current->word);

            linelen = input("> ", &word);
            if (linelen == -1)
            {
                free(word);
                free(dictpath);
                free_dict(dict);
                free_dict(words);
                printf("Error: failed to read input from stdin\n");
                return 1;
            }
            else if (linelen > 0)
                word[linelen - 1] = '\0';
        }
    }

    free(word);
    free(dictpath);
    free_dict(dict);
    if (words_init == 1)
        free_dict(words);

    return 0;
}
