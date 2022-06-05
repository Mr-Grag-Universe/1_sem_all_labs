//
// Created by степан on 02.10.2021.
//
#include <stdio.h>
#include <stdlib.h>

void get_line1(char ** s, int * n) {
    int i = 0;
    char * S = (char*)malloc(i*sizeof(char));
    do {
        char* temp = (char*)realloc(S, (i+1)* sizeof(char));
        S = temp;
        scanf("%c", S+i);
        if (S[i] == EOF) S[i] = '\n';
        i++;
    } while (S[i-1] != '\n');

    //scanf("%80[^\n]", )
    /*do {
        char* temp = (char*)realloc(S, (i+1)* sizeof(char));
        S = temp;
        i++;
    } while (scanf("%c", S+i-1) != EOF);*/
    S[i-1] = '\0';
    /*
    while (scanf("%5[^\n]", S+(i-1)*5)) {
        S = (char*) realloc(S, 5*(i+1)* sizeof(char));
        i++;
    }
    */
    //printf("%c", S[i-2]);
    *n = i;
    *s = S;
}
