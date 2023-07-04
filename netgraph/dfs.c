#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

void storeArray(FILE *in, int *dst) {
    int ch;
    int i = 0;
    
    while ((ch = fgetc(in)) != EOF) {
        if(isdigit(ch)) {
            // printf("%d \n ", ch - '0');
            *dst = ch - '0';
            dst++;
        }
    }
}

void printArray(int *target, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *target);
            target++;
        }
        printf("\n");
    }
}

// void printArrayAt(int *target, int size, int row) {
//     target += size * (row - 1);
//     for (int i = 0; i < size; i++) {
//         printf("%d ", *target);
//         target++;
//     }
//     printf("\n");
// }

int searchRow(int *target, int size, int row, int *flag) {
    target += size * row;
    int offset = 0;
    for (int i = 0; i < size; i++) {
        if(*target == 1 && flag[offset] == 0) break;
        else offset++;
        target++;
    }
    return offset;
}

void printFlag (int *flag, int size) {
    for (int i = 0; i < size; i++) {
        printf("[%d] : %d\n", i, *flag);
        flag++;
    }
}

int main(int argc, char **argv) {
    const char fname[] = "data/search_100d.dat";

    FILE *fp = fopen(fname, "r");

    if (!fp) {
        perror("fopen");
        return 1;
    }

    printf("Opended file: %s \n", fname);

    char cr;
    int size = countLines(fp);

    int *data = (int *)malloc(size * size * sizeof(int));
    int *flag = (int *)malloc(size * sizeof(int));
    int *result = (int *)malloc(size * sizeof(int));

    // disini tambahin buat tracking index result

    // Awal harus gini (soalnya start dari 0)
    flag[0] = 1;
    result[0] = 0;

    // printf("lines : %d\n", size);
    storeArray(fp, data);
    // printArray(data, size);
    // printArrayAt(data, size, 10);

    // misal udah jalan sekali, cuma blm updat resultnya
    flag[searchRow(data, size, 0, flag)] = 1;
    printf("first 1 in :%d\n", searchRow(data, size, 1, flag));
    printFlag(flag, size);

    free(data);
    free(flag);
    free(result);
    return 0;
}