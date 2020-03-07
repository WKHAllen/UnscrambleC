#include "unscramble.h"
#include <stdlib.h>
#include <string.h>

void string_erase(char *word, int index)
{
    for (int i = index; word[i] != '\0'; i++)
        word[i] = word[i + 1];
}

int check_char(const char *word, char chr)
{
    for (int i = 0; word[i] != '\0'; i++)
        if (chr == word[i])
            return i;
    return -1;
}

int check_word(const char *word1, const char *word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 != len2)
        return UNSCRAMBLE_FALSE;

    int index;
    char *letters = strdup(word2);
    for (int i = 0; i < len1; i++) {
        index = check_char(letters, word1[i]);
        if (index != -1)
            string_erase(letters, index);
        else
        {
            free(letters);
            return UNSCRAMBLE_FALSE;
        }
    }

    free(letters);
    return UNSCRAMBLE_TRUE;
}

Dict *unscramble(Dict *dict, char *word)
{
    Dict *words = new_dict();
    Dict *words_tail = words;
    Dict *current = dict->next;

    while (current != NULL)
    {
        if (check_word(word, current->word) == UNSCRAMBLE_TRUE)
        {
            dict_set_next_word(words_tail, current->word);
            words_tail = words_tail->next;
            words->size++;
        }
        current = current->next;
    }
    
    return words;
}
