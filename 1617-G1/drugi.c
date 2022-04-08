#include <stdio.h>

int main()
{
    int arr[100][100];
    int br[100];
    int k = 0;
    int n = 45371;

    while (n != 0) {
        br[k++] = n % 10;
        n = n / 10;
    }
    for (int i = 0; i < k; i++) {
        arr[0][i] = br[k-i-1];
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i % 2 == 0) {
                arr[i][j] = arr[i-1][j]-2;
            } else {
                arr[i][j] = arr[i-1][j]-1;
            }
            if (arr[i][j] < 0) {
                arr[i][j] = 10 + arr[i][j];
            }
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%5d", arr[i][j]);
        }
        printf("\n\n");
    }



    return 0;
}
