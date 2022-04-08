#include <stdio.h>
#include <string.h>

int ponavljanja(char * str, char * needle) {
    int occurances = 0;
    char * ptr, *last = NULL;
    for (ptr = str; (last = strstr(ptr, needle)); ptr = last+1) occurances++;
    return occurances;
}

int main() {

    char str[100] = "BBDDADADA";
    char p[100] = "ABBDA";
    char slova[100];
    int brSlova = 0;

    for (int i = 0; i < strlen(p); i++) {
        if (brSlova == 0) {
            slova[brSlova++] = p[i];
        } else {
            int exists = 0;
            for (int j = 0; j < brSlova; j++) {
                if (slova[j] == p[i]) {
                    exists = 1;
                    break;
                }
            }
            if (exists == 0) {
                slova[brSlova++] = p[i];
            }
        }
    }
    for (int i = 0; i < brSlova; i++) {
        int j = 0;
        char needle[100];
        strcpy(needle, p);
        int len = strlen(needle);
        while (j < len) {
            if (needle[j] == slova[i]) {
                for (int k = j; k < len; k++) {
                    needle[k] = needle[k+1];
                }
                len--;
            } else {
                j++;
            }
        }
        
        printf("%s - %d\n", needle, ponavljanja(str, needle));
    }



    // printf("%d", ponavljanja(str, "ab"));
    return 0;
}