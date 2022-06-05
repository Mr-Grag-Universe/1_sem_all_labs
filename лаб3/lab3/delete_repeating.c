//
// Created by степан on 03.10.2021.
//
#include <stdio.h>
#include <stdlib.h>

void create_dict(char ** S, int size, char **** s, int * n);

void delete_repeating(char * S, int size, char ** s, int * new_size) {

    //double of the entered line
    int new_line_size = size;
    *s = (char*) malloc(sizeof(char)*size);
    for (int i = 0; i < size; ++i) (*s)[i] = S[i];

    //words in the line
    int number_of_words = 0;
    char *** dict;
    create_dict(s, size, &dict, &number_of_words);

    //
    int ws = 0;
    char* word = (char*) malloc(1*sizeof(char));

    //changing of the line
    for (int i = 0; i < new_line_size; ++i) {

        //if it's letter push it to word
        if ((*s)[i] != ' ' && (*s)[i] != '\0') {
            ws++;
            word = (char *) realloc(word, ws*sizeof(char));
            word[ws-1] = (*s)[i];
            continue;
        }

        //if it's not letter chek
        if ((*s)[i] == '\0' || (*s)[i] == ' '){ //cannot work with ,.!?-_ and e.t.

            //is it double-space?
            if (ws == 0) continue;

            for (int k = 0; k < number_of_words; ++k) {

                char flag = 0;
                for (int j = 0; j < ws; ++j) {
                    if (ws != (int) (*dict[k][0]) || word[j] != dict[k][1][j]) {
                        flag = 1;
                        break;
                    }
                }

                //if it's
                if (flag == 0) {
                    if (*dict[k][2] == 0) { *(dict[k][2]) = 1; break; }

                    for (int j = i; j < new_line_size; ++j) (*s)[j - ws] = (*s)[j];

                    i -= ws;
                    new_line_size -= ws;
                    break;
                }
            }

            //delete date of last word
            ws = 0;
            word = (char*) realloc(word, sizeof(char));
        }
    }

    //cut the line
    char * res = (char*) malloc(sizeof(char) * new_line_size);
    for (int j = 0; j < new_line_size; ++j) res[j] = (*s)[j];
    free(*s);
    *s = res;
    *new_size = new_line_size;
    free(word);
    free(dict);
}

void create_dict(char ** S, int size, char **** s, int * n) {
    //array for word in line
    char* word = (char*) malloc(sizeof(char));
    int* word_size = (int*) malloc(sizeof(int));
    *word_size = 0;

    //creation of dictionaries
    char *** dict = (char***) malloc(sizeof(char**));
    int number_of_words = 0;
    for (int i = 0; i < size; ++i) {
        //if it's letter push it to word
        if ((*S)[i] != ' ' && (*S)[i] != '\0') {
            (*word_size)++;
            word = (char *) realloc(word, (*word_size)*sizeof(char));
            word[(*word_size)-1] = (*S)[i];
            continue;
        }

        //if it's not letter chek
        if ((*S)[i] == '\0' || (*S)[i] == ' '){
            //is it double-space?
            if (!(*word_size)) continue;

            char there_is = 0;
            for (int j = 0; j < number_of_words; ++j) {
                char flag = 0;
                for (int k = 0; k < *dict[j][0]; ++k) {
                    if (k == *dict[j][0] || word[k] != dict[j][1][k]) { flag = 1; break; }
                }
                if (flag == 0) { there_is = 1; break; }
            }

            if (there_is == 0) {
                number_of_words++;
                dict = (char ***) realloc(dict, number_of_words * (sizeof(char *) * 10));

                //links to the size (in char) and word
                char **word_c = (char **) malloc(sizeof(char *)*2 + sizeof(int *));

                char * flag = (char*)malloc(sizeof(char));
                *flag = 0;
                word_c[2] = (char *) realloc(flag, sizeof(char));

                word_c[1] = (char *) realloc(word, sizeof(char));
                word_c[0] = (char *) realloc(word_size, sizeof(int));
                dict[number_of_words - 1] = word_c;

                //delete date of last word
                word_size = (int *) malloc(sizeof(int));
                *word_size = 0;
                word = (char *) malloc(sizeof(char));
            }
            else {
                //delete date of last word
                *word_size = 0;
                word = (char *) realloc(word, sizeof(char));
            }
        }
    }
    free(word);
    free(word_size);
    *n = number_of_words;
    *s = dict;
}