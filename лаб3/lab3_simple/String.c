//
// Created by степан on 14.10.2021.
//

int str_len(char * s) {
    int i = 0;
    if (!s) return 0;
    while (s[i]) i++;
    return i;
}

char strcmp_(char * word1, char * word2) {
    int i = 0;
    while (word1[i] && word2[i]) {
        if(word1[i] != word2[i]) break;
        i++;
    }
    if (word1[i] == word2[i]) return 1;
    return 0;
}

void memcpy_(char * start, const char * buf, int len) {
    for (int i = 0; i < len; i++) {
        //if (start[i] == '\0') return;
        start[i] = buf[i];
    }
    //start[len] = '\0';
}
