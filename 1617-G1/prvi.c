#include <stdio.h>
#include <math.h>

double f_rek(int n, int i) {
    if (n < i) return 0;
    double br = (double) (i % 2 == 1 ? 2 : 1) / (double) i;
    printf("%f\n", sqrt(br));
    return sqrt(br + f_rek(n, i+1));
}

double f(int n) {
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        double br = (double) (i % 2 == 1 ? 2 : 1) / (double) i;
        sum = sqrt( br + sum);
    }
    return sum;
}

int main()
{
    int n = 2;
    //printf("%lf\n", f(n));
    printf("%lf\n", f_rek(n,1));
    return 0;
}
