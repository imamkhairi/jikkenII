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

void print (int *target, int size) {
    for (int i = 0; i < size; i++) {
        printf("[%d] : %d\n", i, *target);
        target++;
    }
}

int countFlag (int *flag, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += flag[i];
    }
    return result;
}

void stackPush (int *stack, int data) {
    while(*stack != 0) stack++;
    *stack = data;
}

void stackPop (int *stack) {
    while(*stack != 0) stack++;
    *(--stack) = 0;
}

int stackTop (int *stack) {
    while(*stack != 0) stack++;
    return *(--stack);
}

int main(int argc, char **argv) {
    const char fname[] = "data/search_100d.dat";

    FILE *fp = fopen(fname, "r");

    if (!fp) {
        perror("fopen");
        return 1;
    }

    printf("Opended file: %s \n", fname);

    int size = countLines(fp);
    int *data = (int *)malloc(size * size * sizeof(int));
    int *flag = (int *)malloc(size * sizeof(int)); // tandain udh ke sana atau belm. 1 udh. 0 blm
    int *result = (int *)malloc(size * sizeof(int));
    int *stack = (int *)malloc(size * sizeof(int));
    int currentNode = 0; // current node node index

    int *p = result; // pointer to accees result

    stackPush(stack, 69);
    stackPush(stack, 10);
    stackPush(stack, 25);
    stackPop(stack);
    stackPop(stack);
    printf("Stack top: %d\n", stackTop(stack));
    print(stack, size);


    /* Dari bawah sini jadi comment, jadi balikin lagi nanti*/

    // // Initialize
    // flag[currentNode] = 1;
    // *p = currentNode;
    // p++;
    // // result[0] = currentNode;

    // // printf("lines : %d\n", size);
    // storeArray(fp, data);
    // // printArray(data, size);
    // // printArrayAt(data, size, 10);

    // // misal udah jalan sekali, cuma blm updat resultnya
    // currentNode = searchRow(data, size, currentNode, flag); //update currentNode node
    // flag[currentNode] = 1;
    // *p = currentNode;
    // p++;

    // currentNode = searchRow(data, size, currentNode, flag);
    // flag[currentNode] = 1;
    // *p = currentNode;
    // p++;
    // // for (int i = 0; i < size; i ++) {
    // //     printf("first %d in :%d\n", i, searchRow(data, size, i, flag));
    // // }

    // // print(flag, size);
    // print(result, size);
    // printf("Flag sum : %d\n", countFlag(flag, size));

    free(data);
    free(flag);
    free(result);
    free(stack);
    return 0;
}