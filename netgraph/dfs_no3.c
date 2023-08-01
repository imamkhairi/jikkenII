#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

...

int main(int argc, char **argv) {

    ...

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
    
    ...
}