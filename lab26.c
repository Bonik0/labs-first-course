#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
    struct QueueNode* prev;
} QueueNode;

typedef struct Queue {
    struct QueueNode* front;
    struct QueueNode* back;
    int size;
} Queue;

Queue* Init() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->size = 0;
    q->back = q->front = NULL;
    return q;
}

int Empty(Queue* q) {
    return (q->size > 0) ? 0 : 1;
}

Queue* Add(Queue* q, int num) {
    QueueNode* Node = (QueueNode*)malloc(sizeof(QueueNode));
    Node->data = num;
    Node->next = Node->prev = NULL;
    if (Empty(q)) {
        q->back = q->front = Node;
    } else if (q->size == 1) {
        Node->prev = q->front;
        q->front->next = Node;
        q->back = Node;
    } else {
        Node->prev = q->back;
        q->back->next = Node;
        q->back = Node;
    }
    q->size++;
    return q;
}

void Print(Queue* q) {
    QueueNode* Node = q->front;
    while (Node != NULL) {
        printf("%d ", Node->data);
        Node = Node->next;
    }
    printf("\n");
}
int Back(Queue* q) {
    return (q->back != NULL) ? q->back->data : -1;
}

int Front(Queue* q) {
    return (q->front != NULL) ? q->front->data : -1;
}

Queue* Pop(Queue* q) {
    q->front = q->front->next;
    if (q->front != NULL) {
        free(q->front->prev);
        q->front->prev = NULL;
    } else {
        q->back = NULL;
    }
    q->size--;
    return q;
}

void PrintReverse(Queue* q) {
    QueueNode* Node = q->back;
    while (Node != NULL) {
        printf("%d ", Node->data);
        Node = Node->prev;
    }
    printf("\n");
}

Queue* Solve(Queue* q) {
    int num = Front(q), startSize = q->size, count = 0;
    Queue* newQueue = Init();
    while (Front(q) >= num && !Empty(q)) {
        num = Front(q);
        Add(newQueue, num);
        Pop(q);
    }
    if (!Empty(q)) {
        num = Front(q);
        Pop(q);
        int size = newQueue->size, flag = 1;
        int arr[MAX];
        for (int i = 0; i < size; i++) {
            arr[i] = Front(newQueue);
            Pop(newQueue);
        }
        while (!Empty(q)) {
            Add(newQueue, Front(q));
            Pop(q);
        }
        for (int i = size - 1; i > -1; i--) {
            Add(newQueue, arr[i]);
            if (arr[i] < num && flag) {
                Add(newQueue, num);
                flag = 0;
            }
        }
        if (flag) {
            Add(newQueue, num);
        }
        return newQueue;
    } else {
        return newQueue;
    }
}

int main(){
    Queue* root = Init();
    int a;
    scanf("%d", &a);
    do {
        Add(root, a);
        scanf("%d", &a);
    } while (a != -1);
    root = Solve(root);
    PrintReverse(root);
}
