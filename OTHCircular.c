#include <stdio.h>
#include <stdlib.h>

struct DataCilcular {
    struct DataCilcular *prev;
    int data;
    struct DataCilcular *next;
};

typedef struct DataCilcular *node;

node createNode(int data) {
    node new_node = (node)malloc(sizeof(struct DataCilcular));
    new_node->data = data;
    new_node->next = new_node->prev = new_node;
    return new_node;
}

node insertLast(node head, node new_node) {
    if (head == NULL) {
        head = new_node;
    } else {
        node last = head->prev;
        new_node->next = head;
        new_node->prev = last;
        head->prev = new_node;
        last->next = new_node;
    }
    return head;
}

node sortingAscending(node head, node new_node) {
    if (head == NULL) {
        head = new_node;
    } else if (head->data >= new_node->data) {
        node last = head->prev;
        new_node->next = head;
        new_node->prev = last;
        last->next = new_node;
        head->prev = new_node;
        head = new_node;
    } else {
        node curr = head;
        while (curr->next != head && curr->next->data < new_node->data) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        new_node->prev = curr;
        curr->next->prev = new_node;
        curr->next = new_node;
    }
    return head;
}

node ascendingData(node head) {
    node new_head = NULL;
    node curr = head, next;
    do {
        next = curr->next;
        curr->next = curr->prev = curr;
        new_head = sortingAscending(new_head, curr);
        curr = next;
    } while (curr != head);
    return new_head;
}
void viewData(node head) {
    if (head == NULL) {
        printf("Daftar kosong\n");
        return;
    }
    node curr = head;
    do {
        printf("(%p, %d)\n", curr, curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

int main() {
    node head = NULL;
    int N;

    printf("Masukkan jumlah elemen: ");
    scanf("%d", &N);

    if (N < 1 || N > 10) {
        printf("Jumlah elemen tidak valid. Harus antara 1 dan 10.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        int data;
        printf("Masukkan data %d: ", i + 1);
        scanf("%d", &data);
        if (data < 1 || data > 10) {
            printf("Data tidak valid. Harus antara 1 dan 10.\n");
            return 1;
        }
        head = insertLast(head, createNode(data));
    }

    printf("Daftar sebelum pengurutan:\n");
    viewData(head);

    head = ascendingData(head);

    printf("Daftar setelah pengurutan:\n");
    viewData(head);

    return 0;
}
