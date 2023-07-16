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
        printf("[%d] : %d\n", i + 1, *target);
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

// return first index of 1, row disini mulai dari 1
int searchRow(int *data, int size, int row, int *flag) {
    int offset = 0;
    if (row <= size) {
        row--;
        int *p = data + row*size;
        for (int i = 0; i < size; i++) {
            if(*p == 1 && flag[offset] == 0) {
                flag[offset] = 1; //update flag
                break;
            }
            else offset++;
            p++;
        }
        return ++offset;
    } else {
        printf("Search Row: Row exceedede limit");
        return -1;
    }
}

void printResult(int *result, int size) {
    for (int i = 0; i < (size-1) * 2; i+=2) {
        printf("%d: %d -> %d \n",(i+1)/2 + 1 , result[i], result[i+1]);
    }
}

int searchRight(int *result, int size, int target) {
    int last = 2*(size-1)-1;
    int index = last;
    while (result[index] != target && index >= 0) {
        index -= 2;
        // printf("index = %d\n", index);
    }
    return index;
}

int sameLeft(int *result, int size) {
    int current = result[0];
    int count = 1;
    for (int i = 0; i < (size-1) * 2; i += 2) {
        if (result[i] != current) {
            count ++;
            current = result[i];
        }
    }
    return count;
}

void countHeight(int *result, int size) {
    int last = 2*(size-1)-1;    
    // int index = 2*(size-1)-1;
    int height = 1;
    for (int i = last; i >= 0; i -= 2) {
        int index = i;
        int dummy = 1;
        // printf("%d\n", result[i]);
        while(result[index - 1] != 1) {
            index = searchRight(result, size, result[index - 1]);
            dummy += 1;
        }
        if (dummy > height) height = dummy;
    }
    printf("Height = %d\n", height);
}

void countLeaf(int *result, int size) {
    int last = 2*(size-1)-1;
    int *flag = (int *)malloc(size * sizeof(int));
    
    for (int i = 0; i <= last; i += 2) {
        flag[result[i] - 1] = 1;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        count += flag[i];
    }

    printf("Leaf = %d\n", size - count);
    free(flag);
}


int getMax(int *target, int size) {
    int max = target[0]; 
    for (int i = 1; i < size; i++) {
        if(max < target[i]) max = target[i];
    }
    return max;
}

void countChild(int *result, int size) {
    int current = result[0];
    int aSize = sameLeft(result, size);
    int *child = (int *)malloc(aSize * sizeof(int));
    int *c = child;
    for (int i = 0; i < (size-1) * 2; i += 2) {
        if (result[i] == current) {
            *c = *c + 1;
        } else {
            current = result[i];
            c++;
            *c = *c + 1;
        }
    }
    // print(child, aSize);
    printf("Child = %d\n", getMax(child, aSize));
    free(child);
}

int checkFlag(int *flag, int size) {
    // int *p = flag;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (flag[i] == 0) break;
        // p++;
        count++;
    }
    return count;
}

// ga kepake
void storeNeighbour(int *data, int *neighbour, int size) {
    int *p = data;
    int *n1 = neighbour;
    int *n2 = neighbour;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(p[j + i * size] == 1) {
                // printf("%d ", j+1);
                *n1 = j+1;
                n1++;
            }
        }
        n2 += size;
        n1 = n2;
        // printf("\n");
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

void unionData(int *target, int *neighbour, int size, int row) {
    if (row <= size) {
        row--;
        int *t = target;
        int *condition = neighbour + row * size;

        for (int i = 0; i < size; i++) {
            // printf("%d \n", condition[i]);
            if (t[i] && condition[i]) t[i] = 1;
            else t[i] = 0;
        }
    } else {
        printf("Union Data: Row exceeded limit\n");
    }
}

void intersectionData(int *target, int *neighbour, int size, int row) {
    if (row <= size) {
        row--;
        int *t = target;
        int *condition = neighbour + row * size;

        for (int i = 0; i < size; i++) {
            // printf("%d \n", condition[i]);
            if (t[i] || condition[i]) t[i] = 1;
            else t[i] = 0;
        }
    } else {
        printf("Union Data: Row exceeded limit\n");
    }
}

int isEmpty(int *data, int size) {
    for (int i = 0; i < size; i++) {
        if(data[i] == 1) return 0;
    }
    return 1;
}

void BronKerbosch(int *R, int *P, int *X, int size) {
    if(isEmpty(P, size) && isEmpty(X, size)) print(R, size);
    for (int i = 0; i < 1; i++) {
        if (P[i] == 1) {
            int *v = (int *)malloc(size * sizeof(int));
            int *arg1 = (int *)malloc(size * sizeof(int));
            int *arg2 = (int *)malloc(size * sizeof(int));
            int *arg3 = (int *)malloc(size * sizeof(int));
            // int v[size];
            // int r[size];
            // int p[size];
            // int x[size];
            init(v, size);
            v[i] = 1;
            print(v, size);


            // printf("%d\n", i + 1);
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
    init(R, size);

    int *P = (int *)malloc(size * sizeof(int));
    initP(P, size);

    int *X = (int *)malloc(size * sizeof(int));
    init(X, size);   

    // BronKerbosch(R, P, X, size);

    int * dummy = (int *)malloc(size * sizeof(int));

    print(R, size);
    intersectionData(R, data, size, 1);
    // unionData(R, data, size, 1);
    print(R, size);

    // for (int i = 1; i <= size; i++) {
    //     printArrayAt(neighbour, size, i);
    // }
    
    free(R);
    free(P);
    free(X);
    free(data);
    fclose(fp);
}