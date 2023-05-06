#include <stdio.h>

typedef struct pair {
    int key;
    int value;
} pair;

int Max(int a, int b) {
    return a > b ? a : b;
}

void PrintTable(pair data[], int size){
    printf("\n");
    for (int i = 0; i < size; i++){
        printf("%d  %d\n", data[i].key, data[i].value);
    }
}

void Swap(pair* data, int i, int j){
    int k, v;
    k = data[i].key, v = data[i].value;
    data[i].key = data[j].key;
    data[j].key = k;
    data[i].value = data[j].value;
    data[j].value = v;
}

void Forward(pair* data, int i, int maxIndex){
    while (1) {
        int right = i * 2 + 2, left = i * 2 + 1;
        if (Max(right, left) < maxIndex) {
            if (data[i].key >= Max(data[right].key, data[left].key)){
                break;
            }
            else if (data[right].key > data[left].key){
                Swap(data, right, i);
                i = right;
            } else {
                Swap(data, left, i);
                i = left;
            }
        }
        else if (left < maxIndex) {
            if (data[left].key > data[i].key){
                Swap(data, i, left);
                i = left;
            } else {
                break;
            }
        }
        else if (right < maxIndex) {
            if (data[right].key > data[i].key){
                Swap(data, i, right);
                i = right;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void SortHeap(pair* data, int size) {
    for (int i = (size - 2) / 2; i > -1; i--){
        Forward(data, i, size);
    }
    for (int i = size - 1; i > -1; i--){
        Swap(data, i, 0);
        Forward(data, 0, i);
    }
}

int BinarySearch(pair data[], int num, int size) {
    int right = size, left = -1;
    while (left + 1 < right) {
        int mid = (right + left) / 2;
        if (data[mid].key == num) {
            printf("%d\n", data[mid].value);
            return 0;
        }
        if (data[mid].key < num) {
            left = mid;
        } else {
            right = mid;
        }
    }
    printf("no key\n");
    return 1;
}

int main() {
    printf("input size.\n");
    int n;
    scanf("%d", &n);
    pair data[n];
    printf("input key value.\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &data[i].key, &data[i].value);
    }
    SortHeap(data, n);
    PrintTable(data, n);
    printf("search key\n");
    while(1){
        int num;
        scanf("%d", &num);
        BinarySearch(data, num, n);
    }
}