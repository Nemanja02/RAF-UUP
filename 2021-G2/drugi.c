#include <stdio.h>

void ispis(int mat[4][4], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int n = 4;

    int mat[4][4] = {
        {2,6,1,4},
        {3,5,6,8},
        {4,1,8,0},
        {9,6,3,7}
    };
    int mat2[4][4];

    ispis(mat, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat2[i][j] = mat[i][j];
        }
    }

    int i = 0, j = n;

    while (i < j) {
        int temp = mat2[i][i];
        mat2[i][i] = mat[j-1][i];
        mat2[j-1][i] = temp;

        temp = mat2[j-1][j-1];
        mat2[j-1][j-1] = mat2[i][j-1];
        mat2[i][j-1] = temp;

        i++;
        j--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && i + j != n-1) {
                int max = 0;
                if (j-1 >= 0 && mat[i][j-1] % 2 == 0 && mat[i][j-1] > max) max = mat[i][j-1];
                if (i-1 >= 0 && mat[i-1][j] % 2 == 0 && mat[i-1][j] > max) max = mat[i-1][j];
                if (j+1 <= n-1 && mat[i][j+1] % 2 == 0 && mat[i][j+1] > max) max = mat[i][j+1];
                if (i+1 <= n-1 && mat[i+1][j] % 2 == 0 && mat[i+1][j] > max) max = mat[i+1][j];
                mat2[i][j] = max;
            }
        }
    }

    ispis(mat2, n);

    return 0;
}
