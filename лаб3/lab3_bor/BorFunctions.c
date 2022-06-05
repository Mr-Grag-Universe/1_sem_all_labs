//
// Created by степан on 12.10.2021.
//
#include "Bor.h"

struct Bor init_bor() {
    struct Bor bor;
    bor.begin = (struct Forest*) malloc(sizeof(struct Forest));
    //bor.begin->letter = (char*) malloc(sizeof(char));
    bor.begin->letter = '\0';
    //bor.begin->is_not_end = 1;
    bor.begin->i_saw_it = '\0';
    bor.begin->next = (struct Forest**) malloc(sizeof(struct Forest*));
    bor.begin->next[0] = NULL;
    return bor;
}

void add_w(char * str, struct Bor * bor) {
    struct Forest * element = bor->begin;
    int i = 0, j = 0;
    while (str[i] != '\0') {
        //searching for my letter
        while (element->next[j] != NULL && element->next[j]->letter != str[i]) ++j;

        //if it is there
        if (element->next[j] != NULL) {
            element = element->next[j];
            ++i;
            j = 0;
            continue;
        }

        //struct Forest ** temp_next = malloc(sizeof(struct Forest*)*(j+2));
        //for (int k = 0; k < j+1; ++k) temp_next[j] = element->next[j];
        //free(element->next);
        //element->next = temp_next;
        struct Forest ** temp_next = element->next;
        element->next = (struct Forest **) realloc(element->next, (j+2) * sizeof(struct Forest*));
        free(temp_next);

        element->next[j+1] = NULL;
        struct Forest * next_el = (struct Forest * ) malloc(sizeof(struct Forest));
        next_el->next = (struct Forest **) malloc(sizeof(struct Forest*));
        //next_el->is_not_end = 1;
        next_el->i_saw_it = '\0';
        next_el->next[0] = NULL;
        next_el->letter = str[i];
        //printf("%c", (*next_el).letter);
        element->next[j] = (struct Forest *) realloc(next_el, sizeof(struct Forest));
        element = element->next[j];
        ++i;
        j = 0;
    }
    //element->is_not_end = '\0';
}

void recurtion(struct Forest * element) {
    while (*(element->next) != NULL) {
        //if it's not the end
        recurtion(*(element->next));

        //if it's 1 element
        if (element->next[1] == NULL) element->next[0] = NULL;
        //when you cleared next element
        int i = 0;

        if (element->next[0]) { i = 0; element->next[0] = NULL; }
        while (element->next[i] != NULL) i++; //there is mem.pr. probably
        struct Forest ** new_list = (struct Forest **) malloc(sizeof(struct Forest*)*(i+1));

        if (i) i = 1;
        while (element->next[i] != NULL) {
            new_list[i] = element->next[i+1];
            i++;
        }
        new_list[i] = NULL;
        free(element->next);
        element->next = new_list;
    }
    if (*element->next == NULL) {
        free(element->next);
        free(element);
    }
}

void rec_delete_bor(struct Bor * bor) {
    recurtion(bor->begin);
    bor->begin = NULL;
    //free(bor.begin);
    //bor->begin->next[0] = NULL;
    //bor->begin->letter = '\0';
}


//warning, this functions can be dangerous
void print_rec(struct Forest * element) {
    int i = 0;
    while (element->next[i] != NULL) {
        if (element->letter != '\0') printf("%c", element->letter);
        print_rec(element->next[i]);
        ++i;
    }
    if (element->next[0] == NULL) printf("%c\n", element->letter);
}

void print_bor(struct Bor bor) {
    if (bor.begin->next[0] == NULL) { printf("There is not any elements.\n"); return; }
    struct Forest * element = bor.begin;
    print_rec(element);
}

