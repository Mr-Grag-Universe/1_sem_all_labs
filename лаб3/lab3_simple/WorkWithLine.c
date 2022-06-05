//
// Created by степан on 13.10.2021.
//
#include <stdlib.h>
#include "header.h"

void work_with_line(char ** ss, int * size) {
    int line_size = *size;
    char * s = *ss;
    char * res = (char *) malloc(sizeof(char));
    res[0] = '\0';

    char *word1 = (char *) malloc(sizeof(char));
    word1[0] = '\0';
    int word1_size = 0;

    char *word2 = (char *) malloc(sizeof(char));
    word2[0] = '\0';
    int word2_size = 0;

    //work with line and dict
    for (int p = 0; p < line_size+1; ++p) {
        //if it's a letter
        if (s[p] != ' ' && s[p] != '\0' && s[p] != '\n') {
            word1_size++;

            char * new_w = (char *) malloc(sizeof(char) * (word1_size + 1));
            for (int j = 0; j < word1_size; ++j) new_w[j] = word1[j];
            free(word1);
            //word1 = new_w;
            word1 = (char *) realloc(new_w, sizeof(char) * (word1_size + 1));

            word1[word1_size - 1] = s[p];
            word1[word1_size] = '\0';
            continue;
        }

        if (!word1_size) {
            if (s[p] == '\n') {
                int len = str_len(res);
                res = (char*) realloc(res, sizeof(char)*(len+2));
                res[len] = s[p];
                res[len+1] = '\0';
            }
            continue;
        }

        char there_is_no_rep = 1;

        //work with a word in the line "res"
        for (int j = 0; j < p - word1_size; ++j) {
            //create some word
            if (s[j] != ' ' && s[j] != '\0' && s[j] != '\n') {
                word2_size++;

                char * new_w = (char *) malloc(sizeof(char) * (word2_size + 1));
                for (int k = 0; k < word2_size; ++k) new_w[k] = word2[k];
                free(word2);
                //word2 = new_w;
                word2 = (char *) realloc(new_w, sizeof(char) * (word2_size + 1));

                word2[word2_size - 1] = s[j];
                word2[word2_size] = '\0';
                continue;
            }

            if (word2_size == 0) continue;

            //if there is a double
            if (word1_size == word2_size && strcmp_(word1, word2)) {
                int len = str_len(res);
                res = (char*) realloc(res, sizeof(char)*(len+2));
                res[len] = s[p];
                res[len+1] = '\0';
                there_is_no_rep = 0;
                break;
            }

            word2_size = 0;

            free(word2);
            word2 = (char *) malloc(sizeof(char));
            //word2 = (char *) realloc(word2, sizeof(char));

            word2[0] = '\0';
        }

        if (there_is_no_rep) {
            int len = str_len(res);
            res = (char*) realloc(res, sizeof(char)*(len + word1_size + 2));
            for (int i = len; i < len + word1_size + 1; i++) res[i] = word1[i - len];
            res[len + word1_size] = s[p];//' ';
            res[len + word1_size + 1] = '\0';
        }

        word2_size = 0;

        free(word2);
        word2 = (char *) malloc(sizeof(char));
        word2[0] = '\0';

        word1_size = 0;

        free(word1);
        word1 = (char *) malloc(sizeof(char));
        word1[0] = '\0';
    }

    *size = str_len(res);
    free(word1);
    free(word2);
    free(*ss);
    *ss = (char*) realloc(res, sizeof(char)*(str_len(res)+1));
}