#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

...

int main(int argc, char **argv) {

    ...

    while (!queueIsEmpty(queue, qHead, qTail)) {
        do {
            if (queueIsEmpty(queue, qHead, qTail)) {
                if (checkFlag(flag, size) != size) {
                    currentNode = checkFlag(flag, size) + 1;
                    flag[currentNode - 1] = 1;
                    queueEnqueue(queue, size, &qHead, &qTail, currentNode);
                    count++;
                } else {
                    break;
                }
            }
    
    ...
}