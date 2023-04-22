#include <stdio.h>
#include <string.h>
#include <errno.h>

void Usage() {
    printf("Usage: input_Filename output_Fiename");
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

int ScanStudent(FILE * in, student * s) {
    return fscanf(in,"%s\t%c%c\t%c\t%d\t%d\t%d\t%d\t%d\n", s->surname, &s->initial1,&s->initial2, &s->gender, &s->grupNum, &s->math, &s->dm, &s->len, &s->informatic) == 9;
}
int main(int argc, char * argv[]){
    if (argc != 3) {
        Usage();
        return 1;
    }
    student s;
    FILE *out = fopen(argv[2], "w");
    FILE *in = fopen(argv[1], "r");
    if (!(out&&in)){
        perror("Can't open file");
        return 2;
    }
    //int d =1;
    //fprintf(&d,sizeof(d), 1,out);
    while(ScanStudent(in, &s)){
        //printf("%d ", s.informatic);
        fwrite(&s, sizeof(s), 1, out);
        //fprintf(out,"%s %c%c %c %d %d %d %d %d ", s.surname, s.initial1,s.initial2, s.gender, s.grupNum, s.math, s.dm, s.len, s.informatic);
    }
    fclose(out);
    fclose(in);
}