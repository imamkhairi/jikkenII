#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *set(int index) {
    char result[10];
    char prefix[4] = "data";
    char suffix[4] = ".dat";

    // itoa(index, buff, 10);
    // itoa(index, buff, 10);
    sprintf(result, "data%d.dat", 2);
    
    char *p = result;
    return p;
}

int main() {
    char *test = set(2);

    printf("%s", test);
    return 0;
}