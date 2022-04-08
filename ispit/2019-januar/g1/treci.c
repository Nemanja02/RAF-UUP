#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
    int godina,mesec,dan,vreme,val[3];
    struct tnode * next;
} tnode;

int uporedi(tnode * a, tnode * b) {
    if (a->godina < b->godina) return 1;
    if (a->godina > b->godina) return -1;

    if (a->mesec < b->mesec) return 1;
    if (a->mesec > b->mesec) return -1;

    if (a->dan < b->dan) return 1;
    if (a->dan > b->dan) return -1;

    if (a->vreme > b->vreme) return 1;
    if (a->vreme < b->vreme) return -1;

    return -1;
}

tnode * insert(tnode * head, int godina, int mesec, int dan, int vreme, int val1, int val2, int val3) {
    tnode * node = (tnode*)malloc(sizeof(tnode));
    node->godina = godina;
    node->mesec = mesec;
    node->dan = dan;
    node->vreme = vreme;
    node->val[0] = val1;
    node->val[1] = val2;
    node->val[2] = val3;
    node->next = NULL;

    if (!head) return node;

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

tnode * loadFile(tnode * head, char *s) {
    FILE * f;
    f = fopen(s, "r");
    int datum, vreme, val[3];
    while (fscanf(f, "%d %d %d %d %d", &datum, &vreme, &val[0], &val[1], &val[2]) != EOF) {
        int godina,mesec,dan;
        dan = datum % 100;
        datum /= 100;
        mesec = datum % 100;
        datum /= 100;
        godina = datum;
        head = insert(head, godina, mesec, dan, vreme, val[0], val[1], val[2]);
    }
    return head;
}

void ispis(tnode * head) {
    tnode * q = head;
    while(q) {
        printf("%2d.%2d.%4d %2d (%d %d %d)\n", q->dan, q->mesec, q->godina, q->vreme, q->val[0], q->val[1], q->val[2]);
        q = q->next;
    }
}

int raspon(tnode * head, int min, int max) {
    tnode * q = head;
    int count = 0;
    while (q->next) {
        if (q->vreme == 9) {
            float avg = (q->val[0] + q->val[1] + q->val[2]) / 3;
            if (avg < max && avg > min) count++;
        }
        q = q->next;
    }
    return count;
}

int rasponRek(tnode * node, int count, int min, int max) {
    if (node == NULL) return count;
    if (node->vreme == 9) {
        float avg = (node->val[0] + node->val[1] + node->val[2]) / 3;
        if (avg < max && avg > min) count++;
    }
    rasponRek(node->next, count, min,max);
}

int main() {
    tnode * head = NULL;
    head = loadFile(head, "../aqi.txt");
    // ispis(head);
    printf("%d\n", raspon(head, 120, 150));
    printf("%d\n", rasponRek(head, 0, 120, 150));
    return 0;
}