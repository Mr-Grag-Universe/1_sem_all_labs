//
// Created by степан on 12.10.2021.
//
#include <stdlib.h>

void delete_spaces(char ** res, int * new_line_size) {
    char * temp_line = (char*) malloc(sizeof(char) * *new_line_size);
    char flag = 0;
    char it_is_start = 0;
    int num_of_spaces = 0;
    for (int i = 0; i < *new_line_size; ++i) {
        if ((*res)[i] == '\t') (*res)[i] = ' ';
        if ((*res)[i] != ' ') {
            flag = 0;
            temp_line[i-num_of_spaces] = (*res)[i];
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
            temp_line[i-num_of_spaces] = (*res)[i];
        }
    }
    if ((*res)[*new_line_size-2] == ' ') {
        temp_line[*new_line_size-num_of_spaces-2] = '\0';
        num_of_spaces++;
    }
    *new_line_size -= num_of_spaces;
    //free(*res);
    *res = (char *) realloc(temp_line, (*new_line_size + 1)* sizeof(char));
}
