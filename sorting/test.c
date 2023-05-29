#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *set(int index) {
    char result[10];

    sprintf(result, "data%d.dat", index);
    
    char *p = result;
    return p;
}

int main() {
    char *test = set(2);

    printf("%s", test);
    return 0;
}