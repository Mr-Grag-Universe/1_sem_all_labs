#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//формулировка задачи:
//написать программу для поиска ЦЕЛОЧИСЛЕННЫХ корней квадратного уравнения
//использующую ТЕОРЕМУ ВИЕТТА

void entering_min_and_max(int * min, int * max) {
    printf("Enter your boundaries or \"0\" if you want not to change some one.\n");
    int enter = 0;

    printf("Minimum of x: ");
    scanf("%d", &enter);
    if (!enter) { *min = enter; }

    printf("Maximum of x: ");
    scanf("%d", &enter);
    if (!enter) { *max = enter; }
}

void WN_roots_finder(int a, int b, int c) {
    int min = -100, max = 100;

    if (a < 0) {
        a = -a;
        b = -b;
        c = -c;
    }

    printf("If you want to set the search boundaries manually, enter \"1\" to the console.\n");
    printf("Otherwise, the search boundaries will be set automatically.\n");
    char answer[10];
    while ((getchar()) != '\n');
    scanf("%s", answer);

    //позже можно реализовать ввод строки да/нет
    if (answer[0] == '1') {
        entering_min_and_max(& min, & max);
    }

    if (!a) {
        if (b) {
            if (c % b) {
                printf("This equation has not any root.\n");
                return;
                //return 0;
            }
            printf("This equation has only one root: ");
            int x = -c/b;
            if (x < min || x > max) {
                printf("it is not in the search boundaries.\n");
                return;
            }
            printf("%d",x);
            printf(".\n");
            return;
            //return 1;
        }
        if (!c) {
            printf("Every number is a root of this equation.\ninfinite");
            return;
            //return -1;
        }
        printf("This equation has not any roots.\n");
        return;
        //return 0;
    }

    int D = b*b - 4*a*c;

    if (D < 0) {
        printf("This equation has not any roots.\n");
        return;
        //return 0;
    }

    if (!D) {
        if (b % (a*2)) {
            printf("There is not whole-number roots.\n");
            return;
        }
        printf("There is only one root: ");
        printf("%d", -(b/(a*2)));
        printf("\n");
        return;
        //return 1;
    }

    int x1 = 0;
    int x2 = 0;


    /*for (int x1 = min; x1 <= max; ++x1) {
        for (int x2 = min; x2 <= max; ++x2) {
            if ((double) x1 * x2 == (double) c/a) {
                if ((double) x1 + x2 == - (double) b/a) {
                    printf("There is two whole-number roots: ");
                    printf("%d", x1);
                    printf(" and ");
                    printf("%d", x2);
                    printf("\n");
                    return;
                    //return 2;
                }
            }
        }
    }*/

    for (int x = min; x1 <= max; ++x) {
        if (a*x*x + b*x + c == 0) {
            double x2 = (double) c/a/x;
            if (x2 != (int) x2) {
                printf("There is only one whole-number root: ");
                printf("%d\n", x);
            }
            else {
                if (x2 >= min && x2 <= max) {
                    printf("There is two whole-number root: ");
                    //int k = (int) x2;
                    printf("%d  %d\n", x, (int) x2);
                }
                else {
                    printf("There is only one whole-number root: ");
                    printf("%d\n", x);
                }
            }
            //printf("%d\n", x2);

            return;
            //return 1;
        }
    }

    printf("There is not roots.\n");

    //return 0;
}

void test() {
    for (int a = -100; a < 101; ++a) {
        for (int b = -100; b < 101; ++b) {
            for (int c = -100; c < 101; ++c) {
                printf("%d %c %d %c %d\n", a, ' ', b, ' ', c);
                WN_roots_finder(a, b, c);
                //printf("%d \n" normal_squire_finder(a, b, c));
            }
        }
    }
}

int main() {
    printf("Enter a, b and c of your squire equation:\n");
    int a, b, c;

    printf("%s", "a: ");
    scanf("%d", &a);

    printf("%s", "b: ");
    scanf("%d", &b);

    printf("c: ");
    scanf("%d", &c);

    WN_roots_finder(a, b, c);

    //test();

    return 0;
}
