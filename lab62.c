#include <stdio.h>
#include <string.h>
#include <errno.h> 

void Usage() {
    printf("Usage: input_Filename");
}

typedef struct {
    char surname[25];
    char initial1;
    char initial2;
    char gender;
    int grupNum;
    int math;
    int dm;
    int len;
    int informatic;
} student;

int* Sort(int sub[]) {
    for(int i = 0; i < 4; i++){
        for(int j = i; j > 0 && sub[j] < sub[j - 1]; j--){
            sub[j] += sub[j - 1];
            sub[j - 1] = sub[j] - sub[j - 1];
            sub[j] -= sub[j - 1];
        }
    }
    return sub;
}
int main(int argc, char * argv[]) {
    if (argc != 2) {
        Usage();
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Can't open file");
        return 2;
    }
    student s;
    //fscanf(in,"%s %c%c %c %d %d %d %d %d", s.surname, &s.initial1, &s.initial2, &s.gender, &s.grupNum, &s.math, &s.dm, &s.len, &s.informatic) == 9
    while (fread(&s, sizeof(s), 1, in)) {
        //printf("%d ", s.informatic);
        int sub [] = {s.math, s.dm, s.len, s.informatic};
        int *sub1 = Sort(sub);
        //printf("%d ", s.math);
        if ((sub1[0] + sub1[1] > 6 && sub1[0] == 3) || (sub1[0] + sub1[1] == 9)){
            printf("%s %c%c\t%c\t%d\t%d\t%d\t%d\t%d\n", s.surname, s.initial1, s.initial2, s.gender, s.grupNum, s.math, s.dm, s.len, s.informatic);
        }
    }  
    fclose(in);
    return 0;
}