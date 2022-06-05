//
// Created by степан on 12.10.2021.
//
#include <stdlib.h>

void delete_spaces(char ** res, int * new_line_size) {
    //checking
    if (new_line_size == NULL || (*new_line_size) == 0) return;
    if (res == NULL || (*res)[0] == '\0') return;

    int nls = *new_line_size;
    char * s = *res;
    char * temp_line = (char*) malloc(sizeof(char) * (nls+1));
    for (int i = 0; i < nls+1; ++i) temp_line[i] = '\0';

    char flag = 0;
    char it_is_start = 0;
    int num_of_spaces = 0;

    for (int i = 0; i < nls+1; ++i) {
        if (s[i] == '\t') s[i] = ' ';
        if (s[i] != ' ') {
            flag = 0;
            temp_line[i-num_of_spaces] = s[i];//(*res)[i];
            it_is_start = 1;
        }
        else if (!it_is_start) {
            //it_is_start = 1;
            num_of_spaces++;
            continue;
        }
        else if (flag)
            num_of_spaces++;

        else {
            flag = 1;
            temp_line[i-num_of_spaces] = s[i];//(*res)[i];
        }
    }
    //temp_line[*new_line_size-num_of_spaces-1] = '\0';
    if (s[nls-1] == ' ') {
        temp_line[nls-num_of_spaces-1] = '\0';
        num_of_spaces++;
    }
    nls -= num_of_spaces;
    free(s);
    //if (temp_line == NULL) s = NULL;
    *res = (char *) realloc(temp_line, (nls+1) * sizeof(char));
    *new_line_size = nls;
}
