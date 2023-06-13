#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// void setValue(int *dst, int value) {
//     *dst = value;
// }

int setDecimalCount(int c) {
    int p = 1;
    for (int i = 0; i < c; i++) {
        p *= 10;
    }
    return p;
}

void setPoint(int r, int c, double *x, double *y) {

    double *tmp = malloc(2 * sizeof(double));
    int p = setDecimalCount(c);

    for (int i = 0; i < 2; i++ ) {
        int test = rand() % p;
        tmp[i] = (double)(((double)test/p) * r);
        if(tmp[i] > r) {
            printf("exceed the boundary");
            break;
        }
    }

    *x = tmp[0];
    *y = tmp[1];

    free(tmp);
}

int function(int x, int y) {
    return x*x + y*y;
}

int insideCircle (int x, int y, int r) {
    if (function(x,y) <= r*r) return 1;
    else return 0;
}

int square(int r) {
    return r*r;
}

double circleAreaApprox(int in, int out, int r) {
    return ((double)in/(in+out)) * square(2*r);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int r;
    int c; //decimal count
    int iterationCount;

    if (argc > 1) {
        r = atoi(argv[1]);
        c = atoi(argv[2]);
        iterationCount = atoi(argv[3]);
    } else {
        printf("Set r value!");
    }

    double x;
    double y;

    double countInside = 0;
    double countOutside = 0;

    for ( int i = 0; i < iterationCount; i++) {
        setPoint(r, c, &x, &y);
        // printf("x: %lf   y: %lf\n", x, y);

        if(insideCircle(x, y, r)) {
            // printf("dalam\n");
            countInside ++;
        } else {
            // printf("luar\n");
            countOutside ++;
        }
    }

    printf("result \n");
    printf("in: %.0lf  out: %.0lf\n", countInside, countOutside);
    printf("area : %lf\n", circleAreaApprox(countInside, countOutside, r));

    return 0;
}
