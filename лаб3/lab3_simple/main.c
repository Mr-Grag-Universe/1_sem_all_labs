#include <stdlib.h>
#include <stdio.h>
#include "header.h"

void delete_repeatings(const char * S, int size, char ** s, int * new_size) {
    //S[0] = 'o';
    //copy the original line
    int new_line_size = size;
    char * res = (char*) malloc(sizeof(char)*(size+1));
    for (int i = 0; i < size+1; ++i) res[i] = S[i];

    //схлопываем лишние пробелы и табы
    delete_spaces(&res, &new_line_size);

    //remove double-words
    work_with_line(&res, &new_line_size);

    //схлопываем лишние пробелы и табы
    delete_spaces(&res, &new_line_size);

    *s = res;//(char*) realloc(res, sizeof(char)*new_line_size);

    *new_size = new_line_size;
}

int main() {
    //get user's line
    char * S = NULL;
    int len = 0;
    printf("Enter your line hear: ");
    S = get_line_from_lesson();
    len = str_len(S);

    char * s = NULL;
    int new_len = 0;
    delete_repeatings(S, len, &s, &new_len);

    printf("\n%s\n", s);

    free(S);
    free(s);

    return 0;
}
