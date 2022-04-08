#include <stdio.h>

int main() {

    int maxDim = 0, maxX = 0, maxY = 0;
    int n = 6;
    int mat[6][6] = {
        {1,1,1,0,1,0},
        {1,0,0,0,1,1},
        {1,1,1,1,0,1},
        {0,1,1,1,0,1},
        {1,1,1,1,0,1},
        {1,1,1,0,0,1}
    };

    for (int dim = 2; dim < n; dim++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (i + dim <= n && j + dim <= n) {

                    int type = mat[i][j];
                    int stopped = 0;

                    for (int x = i; x < i + dim; x++) {
                        for (int y = j; y < j + dim; y++) {

                            if (mat[x][y] != type) {
                                stopped = 1;
                            }

                        }
                    }

                    if (stopped == 0) {
                        if (maxDim < dim) {
                            maxDim = dim;
                            maxX = i;
                            maxY = j;
                        }
                    }

                }

            }
        }
    }

    printf("Dimenzija:%dx%d, gornji levi ugao: %d, %d", maxDim, maxDim, maxX, maxY);

    return 0;
}