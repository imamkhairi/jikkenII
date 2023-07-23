#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int countLines(FILE *in) {
    char c;
    int count = 0;

    do {
        c = fgetc(in);
        if(c == '\n') count++;
    } while (c != EOF);

    rewind(in);

    return count;
}

void print (int *target, int size) {
    for (int i = 0; i < size; i++) {
        if(*target != 0) printf("[%d] : %d\n", i + 1, *target);
        target++;
    }
}

// row disini mulai dari 1
void printArrayAt(int *data, int size, int row) {
    if (row <= size) {
        row--;
        int *p = data + row*size;
        for (int i = 0; i < size; i++) {
            printf("%d ", p[i]);
        }
        printf("\n");
    } else {
        printf("Print Array: Row exceeded limit\n");
    }
}

void storeArray(FILE *in, int *dst) {
    int ch;
    int i = 0;
    
    while ((ch = fgetc(in)) != EOF) {
        if(isdigit(ch)) {
            *dst = ch - '0';
            dst++;
        }
    }
}

void initP(int *target, int size) {
    for(int i = 1; i <= size; i++) {
        target[i - 1] = 1; 
    }
}

void init(int *target, int size) {
    for (int i = 1; i <= size; i++) {
        target[i-1] = 0;
    }
}

void unionData(int *target, int *condition, int *data, int size, int row) {
    if (row <= size) {
        row--;
        int *t = target;
        int *c_1 = condition;
        int *c_2 = data + row * size;

        for (int i = 0; i < size; i++) {
            // printf("%d \n", condition[i]);
            if (c_1[i] || c_2[i]) t[i] = 1;
            else t[i] = 0;
        }
    } else {
        printf("Union Data: Row exceeded limit\n");
    }
}

void intersectionData(int *target, int *condition, int *data, int size, int row) {
    if (row <= size) {
        row--;
        int *t = target;
        int *c_1 = condition;
        int *c_2 = data + row * size;

        for (int i = 0; i < size; i++) {
            // printf("%d \n", condition[i]);
            if (c_1[i] && c_2[i]) t[i] = 1;
            else t[i] = 0;
        }
    } else {
        printf("Intersection Data: Row exceeded limit\n");
    }
}

int isEmpty(int *data, int size) {
    for (int i = 0; i < size; i++) {
        if(data[i] == 1) return 0;
    }
    return 1;
}

void BronKerbosch(int *R, int *P, int *X, int *data, int size) {
    int *r = R;
    int *p = P;
    int *x = X;
    int *d = data;

    if(isEmpty(p, size) && isEmpty(x, size)) {
        printf("Result\n");
        print(r, size);
        printf("\n");
    } else {
        for (int i = 0; i < size; i++) {
        // for (int i = 0; i < 1; i++) {
            if (P[i] == 1) {
                int *v = (int *)malloc(size * sizeof(int));
                int *arg1 = (int *)malloc(size * sizeof(int));
                int *arg2 = (int *)malloc(size * sizeof(int));
                int *arg3 = (int *)malloc(size * sizeof(int));
                init(v, size);
                init(arg1, size);
                init(arg2, size);
                init(arg3, size);
                
                v[i] = 1;
                unionData(arg1, r, v, size, 1);
                intersectionData(arg2, p, d, size, i+1);
                intersectionData(arg3, x, d, size, i+1);

                BronKerbosch(arg1, arg2, arg3, d, size);

                P[i] = 0;
                unionData(x, x, v, size, 1);

                free(v);
                free(arg1);
                free(arg2);
                free(arg3);
            }
        }
    }
}

int main(int argc, char **argv) {
    char *file;

    if (argc == 2) {
        file = argv[1];
    } else {
        printf("Set File Name!");
    }

    const char *dir = "data/";
    char fileName[50];
    sprintf(fileName, "%s%s", dir, file);

    FILE *fp = fopen(fileName, "r");

    if (!fp) {
        perror("fopen");
        return 1;
    }

    int size = countLines(fp);

    int *data = (int *)malloc(size * size * sizeof(int));
    storeArray(fp, data);

    int *R = (int *)malloc(size * sizeof(int));
    int *P = (int *)malloc(size * sizeof(int));
    int *X = (int *)malloc(size * sizeof(int));
    init(R, size);
    initP(P, size);
    init(X, size);

    BronKerbosch(R, P, X, data, size);

    free(R);
    free(P);
    free(X);
    free(data);
    fclose(fp);
}