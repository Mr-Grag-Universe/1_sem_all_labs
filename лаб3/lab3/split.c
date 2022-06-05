//
// Created by степан on 02.10.2021.
//
#include <stdio.h>
#include <stdlib.h>

void split(char ** S, int size, char **** s, int * n, char symbol) {
    //creation of dictionaries
    char *** dict = (char***) malloc(sizeof(char**));
    int number_of_words = 0;

    //array for word in line
    char * word = (char*) malloc(sizeof(char));
    int* word_size = (int*) malloc(sizeof (int));
    *word_size = 0;

    for (int i = 0; i < size; ++i) {

        //if it's letter push it to word
        if ((*S)[i] != symbol && (*S)[i] != '\0') {
            (*word_size)++;
            word = (char *) realloc(word, (*word_size)*sizeof(char));
            word[(*word_size)-1] = (*S)[i];
            continue;
        }

        //if it's not letter chek
        if ((*S)[i] == '\0' || (*S)[i] == symbol){
            //is it double-space?
            if (!(*word_size)) continue;
            /*
            //checking of a repeating words
            char there_is = 0;
            for (int j = 0; j < number_of_words; ++j) {
                char flag = 0;
                for (int k = 0; k < *dict[j][0]; ++k) {
                    if (k == *dict[j][0] || word[k] != dict[j][1][k]) { flag = 1; break; }
                }
                if (flag == 0) { there_is = 1; break; }
            }
            */
            //insert this word in the dict

            //push new word to the dictionaries
            number_of_words++;
            dict = (char ***) realloc(dict, number_of_words * (sizeof(char *) * 10));

            //links to the size (in char) and word
            char **word_c = (char **) malloc(sizeof(char *) + sizeof(int *));
            word_c[1] = (char *) realloc(word, sizeof(char *));
            word_c[0] = (char *) realloc(word_size, sizeof(int *));
            dict[number_of_words - 1] = word_c;

            //delete date of last word
            word_size = (int *) malloc(sizeof(int));
            *word_size = 0;
            word = (char *) malloc(sizeof(char));
        }
    }

    *n = number_of_words;
    *s = dict;
}
