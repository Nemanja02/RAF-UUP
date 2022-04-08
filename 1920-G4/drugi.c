#include <stdio.h>

int main() {
    int n = 4;
    int mat[4][4] = {
        {3,4,1,6},
        {2,1,3,1},
        {3,4,5,5},
        {2,3,4,5}
    };

    int last = -1;
    int len = 0;
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int curr;
        if (i % 2 == 0) for (int j = 0; j < n; j++) {
            curr = mat[i][j];
            if (last < curr) len++;
            else {
                if (maxLen < len) maxLen = len;
                len = 1;
            }
            last = curr;
            }
        else for (int j = n-1; j >= 0; j--) {
            curr = mat[i][j];
            if (last < curr) len++;
            else {
                if (maxLen < len) maxLen = len;
                len = 1;
            }
            last = curr;
        }
    }

    printf("%d", maxLen);
    return 0;
}