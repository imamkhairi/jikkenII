#include <stdio.h>
#include <stdlib.h>

int  countLines(FILE *in) {
    char c;
    int count = 0;

    do {
        c = fgetc(in);
        if(c == '\n') count++;
    } while (c != EOF);

    rewind(in);

    return count;
}

void store_array(FILE *in, int *p) {
    int x;
    int i = 0;

    while (fscanf(in, "%d", &x) != EOF) {
        p[i] = x;
        i++;
    }
}

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;

    if (argc == 2) {
        if((in = fopen(argv[1], "r")) == NULL) {
            printf("input file name error\n");
            return 1; //kalau mau tambahin return2 ini
        }
    } else {
        printf("No file name stated \n");
        return 2;
    } 

    int lines = countLines(in);

    int *p = malloc(lines * sizeof(int));
    store_array(in, p);

    return 0;
}