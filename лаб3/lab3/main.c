#include <stdio.h>
#include "header.h"

int main() {
    printf("Hello, dear user!\nPlease, enter your line here: ");

    //creation of the dynamic array of symbols == line
    int size = 0;
    char * S ="0";
    get_line(&S, &size);

    int new_size = 0;
    char * s = "0";
    delete_repeating(S, size, &s, &new_size);

    printf("Your line without repeating: ");
    for (int j = 0; j < new_size-1; ++j) printf("%c", s[j]);
    return 0;
}