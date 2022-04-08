#include <stdio.h>
#include <string.h>

int main()
{
    int n = 4;
    int k = 2;

    int mat[4][4] = {
        {8,1,7,5},
        {8,7,4,6},
        {7,4,4,9},
        {0,1,3,7}
    };
     for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int br = 0; br < k; br++) {
        for (int padding = 0; padding < n/2; padding++) {
            int temp = mat[padding][n-padding-1];
            int temp2 = mat[n-padding-1][n-padding-1];
            for (int i = n - padding - 1; i >= padding; i--) {
                mat[padding][i] = mat[padding][i-1];
            }
            mat[padding][padding] = 0;
            for (int i = n - padding-1; i >= padding+1; i--) {
                mat[i][n-padding-1] = mat[i-1][n-padding-1];
            }
            mat[padding + 1][n - padding - 1] = temp;

            temp = mat[n-padding-1][padding];
            for (int i = padding; i < n-padding-1; i++) {
                mat[n-padding-1][i] = mat[n-padding-1][i+1];
            }
            mat[n-padding-1][n-padding-2] = temp2;
            for (int i = padding; i < n-padding-1; i++) {
                mat[i][padding] = mat[i+1][padding];
            }
            mat[n-padding-2][padding] = temp;
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
/// a b c d
/// 0 1 2 3
