#include <string.h>
#include <stdio.h>

int charCmp(char a, char b) {
    if (a == b) return 1;
    if (a > 'Z') a -= 32;
    if (b > 'Z') b -= 32;
    if (a == b) return 1;
    return 0;
}

int main() {

    char str[100] = "amjZdghAshZfgh";

    int i = 0, len = strlen(str);

    // i pocetno slovo

    int seqenceLen = 1;
    int maxLen = 1;
    do {

        // loop ide unazad kako bi se nasla najveca sekvenca pre najmanje
        for (int j = len - 1; j >= i; j--) {
            if (charCmp(str[i], str[j]) == 1) {

                seqenceLen = j - i;
                if (seqenceLen > maxLen) maxLen = seqenceLen;
                seqenceLen = 0;
                break;
            }
        }
        i++;
    } while (i < len);

    printf("Duzina: %d\n", maxLen+1);
    printf("Podstringovi: ");

    i = 0;

    do {
        int increment = 1;
        // loop ide unazad kako bi se nasla najveca sekvenca pre najmanje
        for (int j = len - 1; j >= i; j--) {
            if (charCmp(str[i], str[j]) == 1) {
                seqenceLen = j - i;
                if (seqenceLen == maxLen) {
                    for (int k = i; k <= j; k++) {
                        printf("%c", str[k]);
                    }
                    printf(" ");
                }
            }
        }
        i++;
    } while (i < len);

    return 0;
}