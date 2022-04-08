#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
    int br;
    char oznaka;
    float vreme;
    struct tnode * next;
} tnode;

typedef struct Igraci {
    char oznaka;
    int poeni;
    struct Igraci * next;
} Igraci;

int uporedi(tnode * a, tnode * b) {
    if (a->br > b->br) return 1;
    if (a->br < b->br) return -1;

    if (a->vreme < b->vreme) return 1;
    if (a->vreme > b->vreme) return -1;
    return -1;
}

tnode * push(tnode * head, int br, char oznaka, float vreme) {
    tnode * node = (tnode*)malloc(sizeof(tnode));
    node->br = br;
    node->oznaka = oznaka;
    node->vreme = vreme;
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
    int br; char oznaka; float vreme;
    while (fscanf(f, "%d %c %f", &br, &oznaka, &vreme) != EOF) {
        head = push(head, br, oznaka, vreme);
    }
    return head;
} 

void ispis(tnode * head) {
    tnode *q = head;
    while(q) {
        printf("%2d %c %f\n", q->br, q->oznaka, q->vreme);
        q = q->next;
    }
}

int pozicija(tnode * head, int br, char oznaka) {
    int poz = 1;
    tnode * q = head;
    while (q->next) {
        if (q->br == br) {
            if (q->oznaka == oznaka) {
                return poz;
            }
            poz++;
        }
        q = q->next;
    }
    return 0;
}

int pozicijaRek(tnode * node, int br, int oznaka, int poz) {
    if (node == NULL) return 0;
    if (node->br == br) {
        if (node->oznaka == oznaka) {
            return poz;
        }
        poz++;
    }
    pozicijaRek(node->next, br, oznaka, poz);
}

int count(tnode * head) {
    tnode * q = head;
    int count = 0;
    while (q) {
        count++;
        q = q->next;
    }
    return count;
}

tnode dodaj(Igraci head, char oznaka, int poeni) {
    
}

int main() {
    tnode * head = NULL;
    head = loadFile(head, "trke.txt");
    ispis(head);
    printf("%d\n", pozicijaRek(head, 20, 'a', 1));
    printf("%d\n", pozicija(head, 20, 'a'));
    int n = count(head);
    int brIgraca = 0;
    tnode * q = head;
    Igraci * igraci = NULL;
    while (q->next) {
        
    }

    return 0;
}