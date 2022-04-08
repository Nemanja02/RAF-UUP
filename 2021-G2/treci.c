#include <stdio.h>
#include <string.h>
int main() {
    char str[100] = "hill forest woods lake forest hill sisa";
    char words[100][100];
    int occurance[100];
    int br = 0;
    int i = 0;
    int start = 0, end = 0;
    do {
        if (str[i+1] == ' ' || str[i+1] == '\0') {
            int end = i + 1;
            char rec[100];
            int m = 0;
            for (int j = start; j < end; j++) {
                rec[m++] = str[j];
            }
            rec[m] = '\0';
            
            if (br == 0) {
                strcpy(words[br], rec);
                occurance[br++] = 1;
            } else {
                int exists = 0;
                for (int j = 0; j < br; j++) {
                    if (strcmp(rec, words[j]) == 0) {
                        occurance[j]++;
                        exists = 1;
                        break;
                    }
                }
                if (exists == 0) {
                    strcpy(words[br], rec);
                    occurance[br++] = 1;
                }
            }
            start = i + 2;
            
        }
        i++;
    } while (str[i] != 0);

    int min = occurance[0];
    for (int i = 1; i < br; i++) {
        if (min > occurance[i]) min = occurance[i];
    }
    char remove[100][100];
    int removeIndex = 0;
    for (int i = 0; i < br; i++) {
        if (occurance[i] == min) strcpy(remove[removeIndex++], words[i]);
    }

    i = 0; start = 0; end = 0;
    int len = strlen(str);

    do {
        int increment = 1;
        if (str[i+1] == ' ' || str[i+1] == '\0') {
            
            end = i + 1;
            char rec[100]; int m = 0;
            for (int j = start; j < end; j++) {
                rec[m++] = str[j];
            } rec[m] = '\0';
            for (int j = 0; j < removeIndex; j++) {
                if (strcmp(rec, remove[j]) == 0) {
                    // printf("%s\n", rec);
                    for (int k = 0; k < (end-start)+1; k++) {
                        for (int a = start; a < len;a++) {
                            str[a] = str[a+1];
                        }
                        len--;
                    }
                    increment = 0;
                }
            }
            if (increment == 1) start = i + 2;
        }
        if (increment == 1) i++;
        else {
            i = 0;
            start = 0;
            end = 0;
        }
    } while (i < len);

    if (str[len] == ' ') str[len] = '\0';

    printf("%s", str);
}