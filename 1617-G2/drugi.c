#include <stdio.h>

int main() {
    
    int n = 45371;
    int mat[100][100];
    int arr[100];
    int k = 0;
    while (n != 0) {
        arr[k++] = n % 10;
        n = n/10;
    }
    for (int i = 0; i < k; i++) {
        mat[k-1][i] = arr[k-i-1];
    }

    for (int i = k-2; i >= 0; i--) {
        for (int j = 0; j < k; j++) {
            if (i % 2 == 0) {
                mat[i][j] = mat[i+1][j] + 1;
            } else {
                mat[i][j] = mat[i+1][j] + 2;
            }
            if (mat[i][j] > 9) {
                mat[i][j] -= 10;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}