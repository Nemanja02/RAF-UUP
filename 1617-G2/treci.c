#include <string.h>
#include <stdio.h>

int main() {
    char str[100] = "Recenica koja ima malo nekoliko reci aa aa aaaa aaaaa";
    int n = 5;
    int i = 0;
    int start = 0;
    int end = 0;
    int len = strlen(str);
    do {
        int increment = 1;
        if (str[i+1] == ' ' || str[i+1] == '\0') {
            int end = i+1;
            if (end - start < 5) {
                for (int k = 0; k < (end-start)+1; k++) {
                    for (int j = start; j < len; j++) {
                        str[j] = str[j+1];
                    }
                    len--;
                }
                increment = 0;
            }
            if (increment == 1) start = i+2;
            
        }
        if (increment == 1) i++; 
        else {
            start = 0;
            i = 0;
            end = 0;
        }
    } while (i < len);

    if (str[len] == ' ') {
        str[len] = '\0';
    }

    printf("%s", str);
    
    
    return 0;
}