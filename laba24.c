#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct Node {
  int flag;
  int word;                   
  struct Node* left;          
  struct Node* right;         
} Node;
 
typedef struct stack {
    int data[MAX];
    int size;
} stack;

typedef struct nodestack {
    Node* data[MAX];
    int size;
} nodestack;

typedef struct pair {
    int word;
    int flag;
} pair;

typedef struct stackPair {
    pair data[MAX];
    int size;
} stackPair;

void pInit(stackPair* s){
    s->size = -1;
}

int pEmpty(stackPair* s) {
    return (s->size == -1);
}

void pPush(stackPair* s, pair num) {
    s->size++;
    s->data[s->size] = num;
}

pair pTop(stackPair * s){
    return s->data[s->size];
}

void pPop(stackPair * s){
    s->size--;
}
int PositionOfSimbol(char s) {
    if (s == '(') {
        return 0;
    } else if (s == '+' || s == '-') {
        return 1;   
    } else if (s == '*' || s == '/' || s == '^') {
        return 2;
    }
    return 3;
}

int Pow(int x, int y) {
    int res = 1;
    for(int i = 0; i < y; i++){
        res *= x;
    }
    return res;
}

void Init(stack *s) {
    s->size = 0;
}

int Empty(stack *s) {
    return (s->size == 0);
}

void Push(stack *s,int num) {
    s->size++;
    s->data[s->size] = num;
}

int Top(stack* s) {
    return s->data[s->size];
}
void Pop(stack *s) {
    s->size--;
}

void nInit(nodestack *s) {
    s->size = -1;
}

void nPush(nodestack *s, Node* num) {
    s->size++;
    s->data[s->size] = num;
}

void nPop(nodestack *s) {
    s->size--;
}

Node* nTop(nodestack *s) {
    return s->data[s->size];
}

void InfixToPostfix(char infix[],pair postfix[]) {
    stack s;
    Init(&s);
    char simbol;
    int j = -1;    
    for(int i = 0; infix[i] != '\0'; i++) {
        simbol = infix[i];
        if('0' <= simbol && simbol <= '9') {
            j++;
            int num = 0;
            while('0' <= simbol && simbol <= '9') {
                num = num * 10 + simbol - '0';
                i++;
                simbol = infix[i];
            }
            postfix[j].word = num;
            postfix[j].flag = 1;
            i--;
        } else if (simbol == '(') {
               Push(&s, simbol);
        } else if (simbol == ')') {
                while (Top(&s) != '(') {
                    j++;
                    postfix[j].word = Top(&s);
                    postfix[j].flag = 0;
                    Pop(&s);
                }
                Pop(&s);
        } else {
            while(!Empty(&s) && PositionOfSimbol(simbol) <= PositionOfSimbol(Top(&s))) {
                j++;
                postfix[j].word = Top(&s);
                postfix[j].flag = 0;
                Pop(&s);
            }
            Push(&s, simbol);
        }
    }
    while (!Empty(&s)) {
        j++;
        postfix[j].word = Top(&s);
        postfix[j].flag = 0;
        Pop(&s);
    }
    postfix[j + 1].word = '\0';
    postfix[j + 1].flag = 0;
}

Node* MakeTree(pair postfix[]) {
    nodestack s;
    nInit(&s);
    for (int i = 0; !(postfix[i].word == '\0' && postfix[i].flag == 0); i++) {
        if (!postfix[i].flag) {
            Node* x = nTop(&s);
            nPop(&s);
            Node* y = nTop(&s);
            nPop(&s);
            Node* node = (struct Node*)malloc(sizeof(struct Node));
            node->word = postfix[i].word;
            node->left = y;
            node->flag = 0;
            node->right = x;
            nPush(&s, node);
        } else {
            Node* node = (struct Node*)malloc(sizeof(struct Node));
            node->word = postfix[i].word;
            node->flag = 1;
            node->left = NULL;
            node->right = NULL;
            nPush(&s, node);
        }
    }
    return s.data[0];
}

int Solve(Node* tree) {
    if (tree->flag) {
        return tree->word;
    } else {
       if (tree->word == '+') {
           return Solve(tree->right) + Solve(tree->left);
       } else if (tree->word == '-') {
           return  Solve(tree->left) - Solve(tree->right);
       } else if (tree->word == '*') {
           return  Solve(tree->right) * Solve(tree->left);
       }
       else if (tree->word == '/') {
           return  Solve(tree->left) / Solve(tree->right);
       } else {
           return Pow(Solve(tree->left), Solve(tree->right));
       }
    }
}

int SolveDegree(stackPair * s){
    pair node = pTop(s);
    if (node.flag) {
        pPop(s);
        return node.word;
    } else if (node.word == '-'){
        pPop(s);
        return -SolveDegree(s)+SolveDegree(s); 
    } else if (node.word == '+') {
        pPop(s);
        return SolveDegree(s) + SolveDegree(s);
    } else if (node.word == '*') {
        pPop(s);
        return SolveDegree(s)*SolveDegree(s);
    } else if (node.word == '/'){
        pPop(s);
        int num = SolveDegree(s);
        return SolveDegree(s) / num;
    } else {
        pPop(s);
        int num = SolveDegree(s);
        return Pow(SolveDegree(s), num);
    }

}

void PrintPost(stackPair * s, stackPair * reverse){
    pair node = pTop(s);
    pPop(s);
    if (node.flag){
        pPush(reverse, node);
        return;
        
    } else if (node.word == '^') {
        pair num1;
        num1.word = SolveDegree(s);
        num1.flag = 1;
        num1.word = Pow(SolveDegree(s), num1.word);
        pPush(reverse,num1);
    } else {
        pair node1;
        node1.word =')';
        node1.flag = 0;
        pPush(reverse, node1);
        PrintPost(s, reverse);
        node1.word = node.word;
        pPush(reverse, node1);
        PrintPost(s, reverse);
        node1.word = '(';
        pPush(reverse, node1);
        return;
    } 
}

void SolvePostfix(pair postfix[]) {
    stackPair s, reverse;
    pInit(&s);
    pInit(&reverse);
    for(int i = 0; !(postfix[i].word == '\0' && postfix[i].flag == 0); i++){
        pPush(&s, postfix[i]);
    }
    PrintPost(&s, &reverse);
    while (!pEmpty(&reverse)){
        pair node = pTop(&reverse);
        if (node.flag){
            printf("%d ", node.word);
        } else {
            printf("%c ", node.word);
        }
        pPop(&reverse);
    }
}

void TreeDetour(Node* tree) {
    if (tree != NULL) {
        if (tree->word == '^' && tree->flag == 0) {
            if (tree->left->flag && tree->right->flag) {
                int num = Pow((tree->left->word), (tree->right->word));
                tree->word = num;
                tree->flag = 1;
                tree->left = NULL;
                tree->right = NULL;
            } else {
                int num = Pow(Solve(tree->left), Solve(tree->right));
                tree->word = num;
                tree->flag = 1;
                tree->left = NULL;
                tree->right = NULL;
            }
        }
        if (tree->word != '^') {
            if(tree->flag){
                printf("%d ",tree->word); 
            } else {
                printf("%c ", tree->word);
            }
        }
        TreeDetour(tree->left);
        TreeDetour(tree->right);
    }
}

int main() {
    char infix[MAX];
    int i;
    pair postfix[MAX];
    scanf("%s", infix);
    InfixToPostfix(infix, postfix);
    printf("Postfix with ^: ");
    for (i = 0; !(postfix[i].word == '\0' && postfix[i].flag == 0); i++) {
        if (postfix[i].flag) {
            printf("%d ", postfix[i].word);
        } else {
            printf("%c ", postfix[i].word);
        }
    }
    printf("\n");
    Node* tree = MakeTree(postfix);
    SolvePostfix(postfix);
    printf("\nPostfix with out ^: ");
    TreeDetour(tree);
    free(tree);
}

