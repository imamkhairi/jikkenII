#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    srand(time(NULL));   // Initialization, should only be called once.
    
    for (int i = 0; i < 100000; i++){
        int r = rand() % 100000 - 50000;
        printf("%d \n", r);
    }

}