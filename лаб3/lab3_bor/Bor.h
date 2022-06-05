//
// Created by степан on 07.10.2021.
//
#include <stdio.h>
#include <stdlib.h>

struct Forest {
    char letter;
    //char is_not_end;
    char i_saw_it;
    struct Forest ** next;
    //int * number_of_lines;
};

struct Bor {
    struct Forest * begin;
};

#ifndef A
#define A
struct Bor init_bor();

void add_w(char * str, struct Bor * bor);

void recurtion(struct Forest * element);

void rec_delete_bor(struct Bor * bor);

void print_rec(struct Forest * element);

//void print_bor(struct Bor bor);

struct Bor create_bor(char ** s, int * nls);
#endif
