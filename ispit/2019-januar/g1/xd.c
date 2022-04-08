#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode {
    int godina,mesec,dan,rez1,rez2;
    char tim1,tim2;
    struct tnode * next;
} tnode;

typedef struct Tim {
    char tim;
    int golovi, prim, bodovi;
    struct Tim * next;
} Tim;

int uporedi(tnode * a, tnode * b) {
    if (a->godina < b->godina) return -1;
    if (a->godina > b->godina) return 1;

    if (a->mesec < b->mesec) return -1;
    if (a->mesec > b->mesec) return 1;

    if (a->dan < b->dan) return -1;
    if (a->dan > b->dan) return 1;
}

tnode * insert(tnode * head, int godina, int mesec, int dan, int rez1, int rez2, int tim1, int tim2) {
    tnode * node = (tnode*)malloc(sizeof(tnode));
    node->next = NULL;
    node->godina = godina;
    node->mesec = mesec;
    node->dan = dan;
    node->rez1 = rez1;
    node->rez2 = rez2;
    node->tim1 = tim1;
    node->tim2 = tim2;

    if (!head) {
        return node;
    }
    if (uporedi(head, node) > 0) {
        node->next = head;
        return node;
    }
    tnode * q = head;
    while (q->next && uporedi(q->next, node) < 0) {
        q = q->next;
    }
    if (q->next) {
        node->next = q->next;
        q->next = node;
    } else {
        q->next = node;
    }
    return head;
}

void ispis(tnode * head) {
    tnode * q = head;
    while(q) {
        printf("%d-%d-%d %c %c %d %d\n", q->godina, q->mesec, q->dan, q->tim1, q->tim2, q->rez1, q->rez2);
        q = q->next;
    }
}

tnode * loadFile(tnode * head, char * s) {
    FILE * f;
    f = fopen(s, "r");
    char datum[12], tim1, tim2;
    int rez1,rez2,godina,mesec,dan;
    while (fscanf(f, "%s %c %c %d %d", &datum, &tim1, &tim2, &rez1, &rez2) != EOF) {
        char * token = strtok(datum, "-");
        int krug = 0;
        while (token != NULL) {
            if (krug == 0) godina = atoi(token);
            if (krug == 1) mesec = atoi(token);
            if (krug == 2) dan = atoi(token);
            krug++;
            token = strtok(NULL, "-");
        }

        head = insert(head, godina, mesec, dan, rez1, rez2, tim1, tim2);
    }
    return head;
}

int brojGolova(tnode * head, char tim) {
    tnode * q = head;
    int br = 0;
    while (q->next) {
        if (q->tim1 == tim) br += q->rez1;
        if (q->tim2 == tim) br += q->rez2;

        q = q->next;
    }
    return br;
}

int brojGlovaRek(tnode * node, char tim, int br) {
    if (node == NULL) return br;
    if (node->tim1 == tim) br += node->rez1;
    if (node->tim2 == tim) br += node->rez2;

    brojGlovaRek(node->next, tim, br);
}

int exists(Tim * head, char tim) {
    Tim * q = head;
    while (q) {
        if (q->tim == tim) return 1;
        q=q->next;
    } 
    return 0;
}

Tim * izmeniTim(Tim * tim, char ime, int golovi, int prim) {
    Tim * q = tim;
    while(q->next) {
        if (q->next->tim != ime) {
            q = q->next;
            break;
        }
        q = q->next;
    }
    if (golovi > prim) q->next->bodovi += 3;
    if (golovi < prim) q->next->bodovi += 0;
    if (golovi == prim) q->next->bodovi += 1;
    q->next->golovi += golovi;
    q->next->prim += prim;

    return tim;
}

Tim * dodajTim(Tim * tim, char ime, int golovi, int prim) {
    Tim * node = (Tim*)malloc(sizeof(Tim));
    if (golovi > prim) node->bodovi = 3;
    if (golovi < prim) node->bodovi = 0;
    if (golovi == prim) node->bodovi = 1;
    node->golovi = golovi;
    node->prim = prim;
    node->tim = ime;
    node->next = NULL;
    if (!tim) {
        return node;
    } else {
        Tim * q = tim;
        while (q->next) q = q->next;
        q->next = node;
    }
    return tim;
}

Tim * dodajTimove(tnode * head, Tim * tim) {
    tnode * q = head;
    while (q->next) {

        if (exists(tim, q->tim1) > 0) {
            tim = izmeniTim(tim, q->tim1, q->rez1, q->rez2);
        } else {
            tim = dodajTim(tim, q->tim1, q->rez1, q->rez2);
        }

        if (exists(tim, q->tim2) > 0) {
            tim = izmeniTim(tim, q->tim2, q->rez2, q->rez1);
        } else {
            tim = dodajTim(tim, q->tim2, q->rez2, q->rez1);
        }
        q= q->next;
    }
    return tim;
}

void ispisTimova(Tim * tim) {
    Tim * q = tim;
    while(q) {
        printf("%c %d %d %d\n", q->tim, q->bodovi, q->golovi, q->prim);
        q=q->next;
    }
}

int uporediTim(Tim * a, Tim *b) {
    if (a->bodovi > b->bodovi) return -1;
    if (a->bodovi < b->bodovi) return 1;

    if (a->golovi - a->prim > b->golovi - b->prim) return -1;
    if (a->golovi - a->prim < b->golovi - b->prim) return 1;

    return -1;
}

Tim * dodajSortirano(Tim * tim, int bodovi, int golovi, int prim, char ime) {
    Tim * node = (Tim*)malloc(sizeof(Tim));
    node->next = NULL;
    node->bodovi = bodovi;
    node->golovi = golovi;
    node->prim = prim;
    node->tim = ime;

    if (!tim) {
        return node;
    }
    if (uporediTim(tim, node) > 0) {
        node->next = tim;
        return node;
    }
    Tim * q = tim;
    while (q->next && uporediTim(q->next, node) < 0) q = q->next;
    if (q->next) {
        node->next = q->next;
        q->next = node;
    } else {
        q->next = node;
    }
    return tim;
}

Tim * sortiraj(Tim * tim) {
    Tim * q = tim;
    Tim * sortirano = NULL;
    while(q) {
        sortirano = dodajSortirano(sortirano, q->bodovi, q->golovi, q->prim, q->tim);
        q = q->next;
    }
    return sortirano;
}

int main() {
    tnode * head = NULL;
    head = loadFile(head, "utakmice.txt");
    // ispis(head);
    // printf("%d\n", brojGolova(head, 'c'));
    // printf("%d\n", brojGlovaRek(head, 'c', 0));

    Tim * timovi = NULL;
    timovi = dodajTimove(head, timovi);
    Tim * sortirano = sortiraj(timovi);
    ispisTimova(sortirano);
    
    return 0;
}