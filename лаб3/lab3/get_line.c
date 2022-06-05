//
// Created by степан on 02.10.2021.
//
#include <stdio.h>
#include <stdlib.h>

void get_line(char ** s, int * n) {
    int i = 0;
    char * S = (char*)malloc(i*sizeof(char));
    do {
        char* temp = (char*)realloc(S, (i+1)* sizeof(char));
        S = temp;
        scanf("%c", S+i);
        i++;
    } while (S[i-1] != '\n');
    S[i-1] = '\0';
    *n = i;
    *s = S;
}
