//
// Created by степан on 02.10.2021.
//

#ifndef GET_LINE
#define GET_LINE
char * get_line(int * n);
void get_line1(char ** s, int * n);
#endif //GET_LINE

#ifndef DELETE_SPACES
#define DELETE_SPACES
void delete_spaces(char ** res, int * new_line_size);
void work_with_line(char ** s, int * nls);
#endif

#ifndef MY_STRING
#define MY_STRING
int str_len(char * s);
char strcmp_(char * word1, char* word2);
char * get_line_from_lesson();
void memcpy_(char * start, char * buf, int len);
#endif