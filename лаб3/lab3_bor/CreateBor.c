//
// Created by степан on 11.10.2021.
//

#include "Bor.h"

struct Bor create_bor(char ** s, int * nls) {
    int new_line_size = *nls;
    char * res = *s;
    struct Bor bor = init_bor();
    char* word = (char*) malloc(sizeof(char));
    word[0] = '\0';
    int word_size = 0;
    for (int i = 0; i < new_line_size; ++i) {
        char letter = res[i];
        if (letter != '\0' && letter != ' ') {
            ++word_size;
            word = (char*) realloc(word, sizeof(char)*(word_size+1));
            word[word_size] = '\0';
            word[word_size-1] = letter;
            continue;
        }

        if (word_size == 0) continue;

        add_w(word, &bor);
        word_size = 0;
        free(word);
        word  = (char*) malloc(sizeof(char));
        //word = (char*) realloc(word, sizeof(char));
        word[0] = '\0';
    }
    free(word);
    *nls = new_line_size;
    return bor;
}