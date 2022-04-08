#include <stdio.h>
#include <math.h>

double f_rek(int n) {
    if (n == 0) return 1;
    double koren = (n % 2 == 0 ? 1 : sqrt(2));
    if (n == 1) koren = 1;
    return n + koren / f_rek(n-1);
}

double f(int n) {
    double sum = 1;
    for (int i = 2; i <= n; i++) {
        double koren = (i % 2 == 0 ? 1 : sqrt(2));
        sum = i + koren / sum;
    }
    return sum;
}

int main() {
    printf("%lf\n", f_rek(6));
    printf("%lf", f(6));
    return 0;
}