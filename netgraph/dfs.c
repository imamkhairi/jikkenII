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

void initStack (int *stack, int size) {
    for (int i = 0;i < size; i++) {
        *stack = -1;
        stack++;
    }
}

void stackPush (int *stack, int data) {
    while(*stack >= 0) stack++;
    *stack = data;
}

void stackPop (int *stack) {
    while(*stack >= 0) stack++;
    *(--stack) = -1;
}

int stackTop (int *stack) {
    while(*stack >= 0) stack++;
    return *(--stack);
}

int stackisEmpty (int *stack) {
    if(*stack == -1) return 1;
    else return 0;
}

void printResult(int *result, int size) {
    for (int i = 0; i < (size-1) * 2; i+=2) {
        printf("%d -> %d \n", result[i], result[i+1]);
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

    printf("%s\n", fileName);

    FILE *fp = fopen(fileName, "r");

    if (!fp) {
        perror("fopen");
        return 1;
    }

    printf("Opened file: %s \n", fileName);

    int size = countLines(fp);
    int *data = (int *)malloc(size * size * sizeof(int));
    int *flag = (int *)malloc(size * sizeof(int)); // tandain udh ke sana atau belm. 1 udh. 0 blm
    int *result = (int *)malloc(2 * (size-1) * sizeof(int));
    int *stack = (int *)malloc(size * sizeof(int));
    int currentNode = 0; // current node node index

    int *r = result; // pointer to accees result

    initStack(stack, size);

    // Initialize
    stackPush(stack, currentNode);
    flag[currentNode] = 1;

    storeArray(fp, data);

    // for (int i = 0; i < size - 1; i++) {
    while (!stackisEmpty(stack)) {
        while (!stackisEmpty(stack) && searchRow(data, size, stackTop(stack), flag) >= size) {
            stackPop(stack);
            currentNode = stackTop(stack);
        }

        if (stackisEmpty(stack)) break;
        
        *r = stackTop(stack) + 1;
        r++;
        currentNode = searchRow(data, size, stackTop(stack), flag); 
        stackPush(stack, currentNode);
        flag[currentNode] = 1;
        *r = currentNode + 1; // +1 itu biar jadi 1 ~
        r++;
    }

    // print(stack, size);

    printResult(result, size);

    free(data);
    free(flag);
    free(result);
    free(stack);
    return 0;
}