#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode {
    int rb, ocene[5];
    char predmet[4];
    int brOcena;
    struct tnode * next;
} tnode;

int uporedi(tnode *a , tnode *b) {
    if (a->rb > b->rb) return 1;
    if (a->rb < b->rb) return -1;

    return strcmp(a->predmet, b->predmet);
}

tnode * upis(tnode * head, int rb, int brOcena, char predmet[4], int ocene[5]) {
    tnode * node = (tnode*)malloc(sizeof(tnode));
    node->rb = rb;
    strcpy(node->predmet, predmet);
    node->brOcena = brOcena;
    for (int i = 0; i < brOcena; i++) {
        node->ocene[i] = ocene[i];
    }
    node->next = NULL;
    if (!head) {
        return node;
    }
    if (uporedi(head, node) > 0) {
        node->next = head;
        return node;
    }
    tnode * q = head;
    while (q->next && uporedi(q->next, node) < 0) q = q->next;
    if (q->next) {
        node->next = q->next;
        q->next = node;
    } else {
        q->next = node;
    }
    return head;
}

tnode * loadFile(tnode * head, char * s) {
    FILE * f;
    f = fopen(s, "r");
    char input[256];
    while (fgets(input, sizeof(input), f)) {
        int rb, ocene[5], brOcena = 0;
        char predmet[4];
        int i = 0;
        char * token = strtok(input, " ");
        while (token != NULL) {
            if (i == 0) {
                rb = atoi(token);
            } else if (i == 1) {
                strcpy(predmet, token);
            } else {
                ocene[brOcena++] = atoi(token);
            }
            i++;
            token = strtok(NULL, " ");
        }
        head = upis(head, rb, brOcena, predmet, ocene);
    }
    return head;
}

void ispis(tnode * head) {
    tnode * q = head;
    while(q) {
        printf("%d %s ", q->rb, q->predmet);
        for (int i = 0; i < q->brOcena; i++) {
            printf("%d ", q->ocene[i]);
        }
        printf("\n");
        q = q->next;
    }
}

int main() {
    tnode * head = NULL;
    head = loadFile(head, "oceneRN.txt");
    ispis(head);
    return 0;
}