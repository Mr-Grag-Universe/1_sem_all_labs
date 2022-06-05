#include <stdio.h>
#include <stdlib.h>

void lab1() {
    double  n = 0;
    int n_ = 0;
    int res = 1;

    scanf("Enter your number, please: %lf\n", &n);

    if (n - (double) ((int) n)) {
        printf("You entered not whole number. Would you like to calculate its output?\n");
        char answer = 0;
        scanf("%c", &answer);
        //printf("hi");
        if (answer == '0') { return; }
        while (n - (double) ((int) n)) { n *= 10; }
    }

    n_ = (int) n;

    while (n_ > 0) {
        if (n_%10) { res *= n_%10; }
        n_ /= 10;
    }

    if (res < 0) res = -res;

    if (n)
        printf("Output is %d\n", res);
    else
        printf("You entered 0.\n");
}