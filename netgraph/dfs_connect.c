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

void stackInit(int *stack, int size) {
    int *p = stack;
    for (int i = 0; i < size; i++) {
        *p = -1;
        p++;
    }
}

int stackSearchEmpty(int *stack, int size) {
    int *p = stack;
    int offset = 0;
    while (*p >= 0 && offset < size) {
        p++;
        offset++;
    }
    return offset;
}

void stackPush (int *stack, int size, int data) {
    int *p = stack;
    if(stackSearchEmpty(stack, size) < size) {
        int offset = stackSearchEmpty(stack, size);
        p = p + offset;
        *p = data;
    } else { 
        printf("Stack Push: Stack full, data %d not stored\n", data);
    }
}

void stackPop(int *stack, int size) {
    int *p = stack;
    if(stackSearchEmpty(stack, size) <= size) {
        int offset = stackSearchEmpty(stack, size) - 1;
        if (offset >= 0) {
            p = p + offset;
            *p = -1;
        } else {
            printf("Stack Pop: Stack Already Empty\n");
        }
    } else { 
        printf("Stack Pop: Stack Full\n");
    }
}

int stackTop(int *stack, int size) {
    int *p = stack;
    if(stackSearchEmpty(stack, size) - 1 < size) {
        int offset = stackSearchEmpty(stack, size) - 1;
        if (offset >= 0) {
            p += offset;
        } else {
            printf("Stack Top: Stack is Empty\n");
        }
    } else { 
        printf("Stack Top: Stack Full\n");
    }
    return *p;
}

int stackIsEmpty(int *stack) {
    int *p = stack;
    if (*p == -1) return 1;
    else return 0;
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

    int *stack = (int *)malloc(size * sizeof(int));
    stackInit(stack, size);

    int *data = (int *)malloc(size * size * sizeof(int));
    storeArray(fp, data);

    int *flag = (int *)malloc(size * sizeof(int)); // 1 visited, 0 not yet
    flag[0] = 1;

    int *result = (int *)malloc(2 * size * sizeof(int));
    int *r = result;

    int currentNode = 1;
    stackPush(stack, size, currentNode);

    int count = 1;

    while(!stackIsEmpty(stack)) {
        do {
            if (stackIsEmpty(stack)) {
                if(checkFlag(flag, size) != size) {
                    currentNode = checkFlag(flag, size) + 1;
                    flag[currentNode - 1] = 1;
                    stackPush(stack, size, currentNode);
                    count++;
                } else {
                    break;
                }
            }
            currentNode = searchRow(data, size, stackTop(stack, size), flag);
            if (currentNode > size) stackPop(stack, size);
        } while(currentNode > size);

        if (stackIsEmpty(stack))break;
        *r = stackTop(stack, size);
        r++;
        *r = currentNode;
        r++;
        stackPush(stack, size, currentNode);
    }

    printResult(result, size);
    // countHeight(result, size);
    // countLeaf(result, size);
    // countChild(result, size);

    printf("flag -----\n");
    // print(flag, size);
    printf("count = %d\n", count);
    // printf("stack -----\n");
    // print(stack, size);

    // stackPop(stack, size);
    // printf("stack top %d\n", stackTop(stack, size));

    // print(stack, size);
    free(stack);
    free(data);
    free(flag);
    free(result);
    fclose(fp);
}

