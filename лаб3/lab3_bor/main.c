#include "Bor.h"
#include "header.h"

void delete_repeatings(char const * S, int size, char ** s, int * new_size) {
    //copy the original line
    int new_line_size = size;
    char * res = (char*) malloc(sizeof(char)*size);
    for (int i = 0; i < size; ++i) res[i] = S[i];

    //схлопываем лишние пробелы и табы
    delete_spaces(&res, &new_line_size);

    //create the bor
    struct Bor bor = create_bor(&res, &new_line_size);

    //remove double-words
    work_with_line(&res, &new_line_size, &bor);

    //схлопываем лишние пробелы и табы
    delete_spaces(&res, &new_line_size);

    *s = (char*) realloc(res, sizeof(char)*new_line_size);
    *new_size = new_line_size;
    rec_delete_bor(&bor);
}

int main() {
    //get user's line
    char * S = NULL;
    int len = 0;
    printf("Enter your line hear: ");
    S = get_line(&len);
    //get_line1(&S, &len);

    char * s = NULL;
    int new_len = 0;
    delete_repeatings(S, len, &s, &new_len);

    for (int i = 0; i < new_len; ++i) printf("%c", s[i]);
    printf("\n");

    free(S);
    free(s);

    return 0;
}