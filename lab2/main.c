#include <stdio.h>

long double f1(long double x, long double eps);
long double f2(long double x, int n);

int main() {
    int x = 0, n = 0;
    long double eps = 0;

    printf("Enter x: ");
    if (scanf("%d", &x) <= 0) { printf("Error!!!"); }
    printf("Enter epsilon: ");
    if (scanf("%Lf", &eps) <= 0) { printf("Error!!!"); }
    printf("Enter n: ");
    if (scanf("%d", &n) <= 0) { printf("Error!!!"); }

    printf("%.30Lf\n", f1(x, eps));
    printf("%.30Lf\n", f2(x, n));
    return 0;
}

long double f1(long double x, long double eps) {
    long double res = 0, s1 = 0, p1 = 1, p2 = 0;
    int k = 2;
    p1 = p1*x*x*2;
    res += p1;
    do {
        //printf("%.10Lf %.10Lf %.10Lf ", p1, p2, res);
        p2 = p1;
        s1 = res;
        p1 *= x*x*2/k;
        //printf("%.20Lf %.20Lf\n", p1, p2-p1);
        res += p1;
        k++;
    } while (p1 > eps);
    return res;
}

long double f2(long double x, int n) {
    long double res = 0, p1 = 1, p2 = 0;
    p1 = p1*x*x*2;
    int k = 2;
    res += p1;
    do {
        p2 = p1;
        p1 = p1 * x * x * 2 / k;
        res += p1;
        k++;
    } while (n >= k);
    return res;
}