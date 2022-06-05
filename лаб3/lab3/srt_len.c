//
// Created by степан on 04.10.2021.
//

int str_len(char ** s) {
    int i = 0;
    while ((*s)[i] != '\0') i++;
    return i;
}