//
// Created by степан on 13.10.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>
/*
char * get_line(int * size) {
    char * S = (char *) malloc(sizeof(char)*0);
    char * s = (char *) malloc(sizeof(char)*10);
    int i = 1;
    while (scanf("%10[^\n]", s) > 0) {
        S = (char*) realloc(S, sizeof(char)*10*i);
        for (int j = i*10-10; j < 10*i; ++j) S[j] = s[j-i*10+10];
        //for (int j = 0; j < 10*i; ++j) printf("%c ", S[j]);
        //printf("\n");
        free(s);
        s = (char *) malloc(sizeof(char)*10);
        i++;
    }
    free(s);
    i = 0;
    while (S[i] != '\0') i++;
    //S[i] = '\0';
    S = (char*) realloc(S, sizeof(char)*(i+1));

    //for (int j = 0; j < i+1; ++j) printf("%c", S[j]);
    //printf("\n");
    *size = i+1;
    return S;
}
*/

char * get_line_from_lesson() {
    char buf[81] = {0};
    char * res = (char*) malloc(1);
    res[0] = '\0';
    int len = 0;

    //printf("%d", EOF);
    while (scanf("%80[^\n]", buf) != EOF) {
        int chunk_len = str_len(buf);
        int old_len = str_len(res);

        if (chunk_len == 80) {
            res = (char*) realloc(res, sizeof(char) * (old_len + chunk_len + 1));

            memcpy_(res + old_len, buf, chunk_len);
            res[old_len + chunk_len] = '\0';
        }
        else {
            res = (char *) realloc(res, sizeof(char) * (old_len + chunk_len + 2));

            memcpy_(res + old_len, buf, chunk_len);
            res[old_len + chunk_len + 1] = '\0';
            res[old_len + chunk_len] = '\n';
            scanf("%*c");
        }
        len = str_len(res);
        for (int i = 0; i < 81; ++i) buf[i] = '\0';
    }

    //printf("\n%s\n", res);

    if (len > 0) {
        char * new_res = (char*) malloc(sizeof(char) * len);
        for (int i = 0; i < len; i++) new_res[i] = res[i];
        free(res);
//        res = (char*) realloc(new_res, sizeof(char) * len);
        res = new_res;
        res[len-1] = '\0';
    }
    else res = calloc(1, sizeof(char));

    //res[]

    return res;
}


char * get_line_from_lesson2() {
    char buf[81] = {0};
    char * res = NULL;
    int len = 0;
    int n = 0;
    printf("%d", EOF);
    while (scanf("%80[^\n]", buf) != EOF) {
        res = (char*) realloc(res, sizeof(char) * str_len(buf)+1);
        memcpy(res, buf, str_len(buf)+1);
        scanf("%*c");
    }

    printf("\n%s\n", res);

    if (len > 0) {
        char * new_res = (char*) malloc(sizeof(char) * len);
        for (int i = 0; i < len-1; i++) new_res[i] = res[i+1];
        free(res);
        res = (char*) realloc(new_res, sizeof(char) * len);
        len--;
        res[len] = '\0';
    }
    else res = calloc(1, sizeof(char));

    return res;
}

char * get_line_from_lesson_mod() {
    char buf[81] = {0};
    char * res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        printf("%c", n);
        //if (n < 0) {
        //    if (!res) return NULL;
        //}
        if (n <= 0) scanf("%*c");
        else {
            int chunk_len = str_len(buf);
            int str_len = len + chunk_len + 1;
            res = realloc(res, str_len + 1);
            //memcpy(res + len + 1, buf, chunk_len);
            memcpy_(res + len + 1, buf, chunk_len);
            res[len] = '\n';
            len = str_len;
        }
    } while (n != EOF);

    printf("\n");

    if (len > 0) {

        char * new_res = (char*) malloc(sizeof(char) * len);
        for (int i = 0; i < len-1; i++) new_res[i] = res[i+1];
        free(res);
        res = (char*) realloc(new_res, sizeof(char) * len);
        len--;
        res[len] = '\0';
    }
    else res = calloc(1, sizeof(char));

    return res;
}