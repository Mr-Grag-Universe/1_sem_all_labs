//
// Created by степан on 02.10.2021.
//
//#include "Bor.h"

#ifndef GET_LINE
#define GET_LINE
char * get_line(int * n);
void get_line1(char ** s, int * n);
#endif //GET_LINE

#ifndef DELETE_SPACES
#define DELETE_SPACES
void delete_spaces(char ** res, int * new_line_size);
void work_with_line(char ** s, int * nls, struct Bor * b);
#endif

#ifndef DELETE_REPEATING
#define DELETE_REPEATING
//void delete_repeating(char ** S, int size, char ** s, int * new_size);
#endif
/*
#ifndef CREATE_BOR
#define CREATE_BOR
struct Bor create_bor(char ** s, int * nls);
#endif
*/