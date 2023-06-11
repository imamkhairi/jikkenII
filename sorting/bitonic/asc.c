#include <stdlib.h>
#include <stdio.h>

int main() {
    for (int i = 1; i <= 65536; i++) {
        printf("%d\n", i);
    }
    for (int i = 65537; i >= 2; i--) {
        printf("%d\n", i);
    }
}