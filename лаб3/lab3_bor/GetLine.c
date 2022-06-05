//
// Created by степан on 13.10.2021.
//

#include <stdio.h>
#include <stdlib.h>

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
/*
int main() {
    char * S = get_line();
    //for (int j = 0; j < 10*; ++j) printf("%c", S[j]);
    //printf("\n");
    printf("%s\n", S);
    free(S);
    return 0;
}
*/