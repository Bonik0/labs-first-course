#include <stdio.h>
#include <stdlib.h>

#define MAX_DEEP 15

struct tree {
    int value;
    struct tree *left, *right;
};

struct tree* AddNode(struct tree* node, int num) {
    if (node == NULL) {
        node = (struct tree*)malloc(sizeof(struct tree));
        node->value = num;
        node->left = node->right = NULL;
    } else if (node->value <= num) {
        node->right = AddNode(node->right, num);
    } else {
        node->left = AddNode(node->left, num);
    }
    return node;
}

int IsLeaf(struct tree* node) {
    return ((node->left == NULL) && (node->right == NULL)) ? 1 : 0;
}

void PrintTree(struct tree* node, int deep) {
    deep++;
    if (node != NULL) {
        PrintTree(node->right, deep);
        for (int i = 0; i < deep; i++) {
            printf("   ");
        }
        printf("%d\n", node->value);
        PrintTree(node->left, deep);
    }
}

void CheckDiap(struct tree* node, int min, int max, int *ans){
    if (*ans && node != NULL) {
        if (IsLeaf(node)) { 
             *ans = ((node->value <= max) && (node->value >= min));
        } else {
            CheckDiap(node->left, min, max, ans);
            CheckDiap(node->right, min, max, ans);
        }
    }
}

int MinValue(struct tree* node) {
    if (node->left == NULL) {
        return node->value;
    } else {
        return MinValue(node->left);
    }
}

struct tree* Delite(struct tree* node, int num) {
    if (node == NULL) {
        return node;
    }
    if (num < node->value) {
        node->left = Delite(node->left, num);
    } else if (num > node->value) {
        node->right = Delite(node->right, num);
    } else if (IsLeaf(node)) {
        free(node);
        node = NULL;
    } else if (node->right == NULL) {
        struct tree* nodeleft = node->left;
        free(node);
        node = nodeleft;
    } else if ((node->left == NULL)) {
        struct tree* noderight = node->right;
        free(node);
        node = noderight;
    } else {
        node->value = MinValue(node->right);
        node->right = Delite(node->right, node->value);
    } 
    return node;
}

int main() {
    struct tree* root = NULL;
    int numNow = 1, minDiap, maxDiap, ans = 1, s1 = 0;
    char s = ' ';
    printf("enter diapason: min, max: ");
    scanf("%d", &minDiap);
    scanf("%d", &maxDiap);
    printf("enter values: ");
    do {
        scanf("%d", &numNow);
        root = AddNode(root, numNow);
        s = getchar();
    } while (s == ' ');
    while (s1 != 5) {
        printf("\nenter command:\n 1 - add node\n 2 - print tree \n 3 - check diap \n 4 - delite node\n 5 - stop\n");
        scanf("%d", &s1);
        switch (s1) {
            case 1:
                scanf("%d", &numNow);
                root = AddNode(root, numNow);
                break;
            case 2:
                PrintTree(root, 0);
                break;
            case 3:
                CheckDiap(root, minDiap, maxDiap, &ans);
                if (ans) {
                    printf("all leaves in diap");
                } else {
                    printf("leaves not in diap");
                }
                ans = 1;
                break;
            case 4:
                scanf("%d", &numNow);
                root = Delite(root, numNow);
                break;
            default:
                break;
        }
    }
}
