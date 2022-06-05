//
// Created by степан on 13.10.2021.
//
#include "Bor.h"
#include <stdlib.h>

void work_with_line(char ** s, int * nls, struct Bor * b) {
    struct Bor bor = *b;
    int new_line_size = *nls;
    char *res = *s;
    char *word = (char *) malloc(sizeof(char));
    word[0] = '\0';
    int word_size = 0;

    //work with line and dict
    for (int p = 0; p < new_line_size; ++p) {
        if (res[p] != ' ' && res[p] != '\0') {
            word_size++;
            /*char * new_w = (char *) malloc(sizeof(char) * (word_size + 1));
            for (int j = 0; j < word_size; ++j) new_w[j] = word[j];
            free(word);
            word = new_w;*/
            word = (char *) realloc(word, sizeof(char) * (word_size + 1));
            word[word_size - 1] = res[p];
            word[word_size] = '\0';
            continue;
        }

        //work with a word in the line "res"
        struct Forest *element = bor.begin;
        int i = 0, j = 0;
        while (word[i] != '\0') {
            while (element->next[j] != NULL && element->next[j]->letter != word[i]) ++j;

            //go to the next element
            if (element->next[j]) {
                element = element->next[j];
                ++i;
                j = 0;
                continue;
            }
            ++i;
            j = 0;
        }

        if (!element->i_saw_it) element->i_saw_it = 1;

        else {
            char *new_res = (char *) malloc(sizeof(char) * (new_line_size - word_size+1));
            for (int k = 0; k < p - word_size; ++k)
                new_res[k] = res[k];
            for (int k = p; res[k] && k < new_line_size; ++k)
                new_res[k - word_size] = res[k];

            free(res);
            res = (char *) realloc(new_res, sizeof(char) * (new_line_size - word_size+1));

            p -= word_size;
            new_line_size -= word_size;
        }

        word_size = 0;
        free(word);
        word = (char *) malloc(sizeof(char));
        word[0] = '\0';
    }
    *nls = new_line_size;
    free(word);
    //free(*s);
    *s = (char*) realloc(res, sizeof(char)*new_line_size);
}