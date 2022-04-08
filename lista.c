#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ucenik {
    char smer[3];
    int index, godina, brKlk;
    float bodovi[5], ukupno;
    struct ucenik * next;
} ucenik;

typedef struct ocene {
    int n;
    int raspon[100];
} ocene;

int uporedi(ucenik * a, ucenik * b) {
    if (a->ukupno > b->ukupno) return -1;
    if (a->ukupno < b->ukupno) return 1;
    return -1;
}

ucenik * dodaj(ucenik * head, char smer[3], int index, int godina,float bodovi[5], int brKlk) {
    ucenik * node = (ucenik*)malloc(sizeof(ucenik));
    node->next = NULL;
    node->index = index;
    node->godina = godina;
    node->brKlk = brKlk;
    node->ukupno = 0;
    strcpy(node->smer, smer);
    for (int i = 0; i < brKlk; i++) {
        node->bodovi[i] = bodovi[i];
        node->ukupno += bodovi[i];
    }
    if (!head) {
        return node;
    }

    if (uporedi(head, node) > 0) {
        node->next = head;
        return node;
    }

    ucenik * q = head;
    while (q->next && uporedi(q->next, node) < 0) q = q->next;

    if (q->next) {
        node->next = q->next;
        q->next = node;
    } else {
        q->next = node;
    }
    return head;
}

ucenik * loadFile(char * s, ucenik * head) {
    FILE * f;
    f = fopen(s, "r");
    char input[256];
    while (fgets(input, sizeof(input), f)) {
        char * token = strtok(input, ",");
        int krug = 0;
        int index, godina, brKlk = 0;
        float bodovi[5];
        char smer[3];
        while (token != NULL) {
            if (krug == 0) strcpy(smer, token);
            if (krug == 1) index = atoi(token);
            if (krug == 2) godina = atoi(token);
            if (krug > 2) {
                bodovi[brKlk++] = atof(token);
            }
            krug++;
            token = strtok(NULL, ",");
        }
        head = dodaj(head, smer, index, godina, bodovi, brKlk);
    }
    return head;
}

void ispis(ucenik * head) {
    ucenik * q = head;
    int count = 0;
    while (q) {
        count++;
        printf("%s %d/%d %d", q->smer, q->index,q->godina, q->ukupno);
        for (int i = 0; i < q->brKlk; i++) {
            printf("%3.2f ", q->bodovi[i]);
        }
        printf("\n");
        q = q->next;
    }
    printf("Ukupno: %d\n", count);
}

int najveciIndex(ucenik * head, char smer[3], int godina) {
    int max = 0;
    ucenik * q = head;
    while (q) {
        if (strcmp(smer, q->smer) == 0 && q->godina == godina && max < q->index) max = q->index;
        q= q->next;
    }
    return max;
}

int najveciIndexRek(ucenik * node, char smer[3], int godina, int max) {
    if (!node) return max;
    if (strcmp(smer, node->smer) == 0 && node->godina == godina && max < node->index) max = node->index;
    najveciIndexRek(node->next, smer, godina, max);
}

int maxBodovi(ucenik * head) {
    float max = 0;
    ucenik * q = head;
    while (q) {
        if (q->ukupno > max) max = q->ukupno;
        q= q->next;
    }
    return (int )floor((double)max);
}

ocene * dodajOcene(ucenik * head) {
    ocene * o = (ocene*)malloc(sizeof(ocene));
    ucenik * q = head;
    int max = maxBodovi(head);
    o->n = max/10+1;
    for (int i = 0; i < o->n; i++) {
        o->raspon[i] = 0;
    }

    while(q) {
        o->raspon[(int)floor((double)q->ukupno)/10]++;
        q = q->next;
    }
    return o;
}

void ispisOcena(ocene * o) {
    
    for (int i = 0; i < o->n; i++) {
        printf("%d-%d : %d\n", i*10, (i+1)*10, o->raspon[i]);
    }
}

int main() {
    ucenik * head = NULL;
    head = loadFile("studenti-UUP.txt", head);
    ispis(head);
    printf("%d\n", najveciIndex(head, "RI", 2020));
    printf("%d\n", najveciIndexRek(head, "RI", 2020, 0));
    ocene * ocene = NULL;
    ocene = dodajOcene(head);
    ispisOcena(ocene);
    return 0;
}