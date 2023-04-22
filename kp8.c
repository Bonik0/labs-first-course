#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef enum {
    red,
    white,
    green,
    blue,
    yellow
} color;

typedef struct node {
    color value;
    struct node* next;
} node;


node* InitList(color value) {
    node* root = (node*)malloc(sizeof(node));
    node* root1 = (node*)malloc(sizeof(node));
    root1->next = NULL;
    root1->value = value;
    root->next = root1;
    return root;
}

void Add(node* root, color value) {
    while (root->next != NULL) {
        root = root->next;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->value = value;
    root->next = temp;
}

void InsertList(node* root, color value, int number) {
    int count = 1;
    while (count != number) {
        if (root->next != NULL) {
            root = root->next;
            count++;
        } else {
            printf("ERROR");
        }
    }
    node* next = root->next;
    node* now = (node*)malloc(sizeof(node));
    root->next = now;
    now->value = value;
    now->next = next;
}

void PrintList(node* root) {
    root = root->next;
    while(root != NULL) {
        switch(root->value) {
            case white:
                printf("white ");
                break;
            case red:
                printf("red ");
                break;
            case green:
                printf("green ");
                break;
            case blue:
                printf("blue ");
                break;
            case yellow:
                printf("yellow ");
                break;
        }
        root = root->next;
    }
}

int LenList(node* root) {
    root = root->next;
    int count = 1;
    while (root->next != NULL) {
        count++;
        root = root->next;
    }
    return count;
}

void Solve(node* root){
    int len = LenList(root);
    if (len < 4){
        printf("Error");
        return;
    }
    color num1, num2;
    int count = 1;
    root = root->next;
    node* l = root;
    num1 = l->next->value;
    while(count != len - 1){
        count++;
        l = l->next;
    }
    num2 = l->value;
    count = 1;
    root->next->value = num2;
    while(count != len - 1){
        count++;
        root = root->next;
    }
    root->value = num1;
}

void DeleteList(node* root, int num) {
    if (num > LenList(root)){
        printf("ERROR");
    }
    int count = 0;
    node* item;
    node* temp = root;
    while (count != num - 1) {
        temp = temp->next;
        count++;
    }
    item = temp->next;
    if (item->next == NULL) {
        temp->next = NULL;
    } else {
        temp->next = item->next;
    }
    free(item);
}
int Check(char s[]){
    switch(s[0]){
        case 'w':
            return 1;
        case 'r':
            return 0;
        case 'b':
            return 3;
        case 'g':
            return 2;
        case 'y':
            return 4;   
    }
    return 0;
}
int main() {
    printf("Input first elem: ");
    char s[6];
    scanf("%s", s);
    node* root = InitList(Check(s));
    printf("\n 1.Add 2. insert 3. delete 4. len 5. Swap 6. exit\n");
    int thatDo, num;
    scanf("%d", &thatDo);
    while(thatDo != 6){
        switch (thatDo){
            case 1:
                scanf("%s", s);
                Add(root, Check(s));
                PrintList(root);
                break;
            case 2:
                scanf("%s", s);
                scanf("%d", &num);
                InsertList(root, Check(s), num);
                PrintList(root);
                break;
            case 3:
                scanf("%d", &num);
                DeleteList(root, num);
                PrintList(root);
                break;
            case 4:
                printf("\n%d\n", LenList(root));
                break;
            case 5:
                Solve(root);
                break;
            case 6:
                thatDo = 6;
                break;
        }
    printf("\n 1.Add 2. insert 3. delete 4. len 5. Swap 6. exit\n");
        scanf("%d", &thatDo);
    }
    printf("\n");
}