#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double getPercentage() {
    double x = rand() % 200;
    x -= 100;
    return x/100;
}

void setPoint(double *point, int r) {
    for (int i = 0; i < 2; i++) {
        double percentage = getPercentage();
        point[i] = percentage*r;
    }
}

double square(double r) {
    return r*r;
}

double circle(double *point){
    return point[0]*point[0] + point[1]*point[1];
}

int insideCircle(double *point, int r){
    if (circle(point) <= r*r) return 1;
    else return 0;
}

double circleAreaApprox(int insideCount, int outsideCount, int r) {
    return ((double)(insideCount)/(double)(insideCount + outsideCount)) * square(2*r);
}

void printResult(int insideCount, int outsideCount, int r) {
    printf("in: %d, out: %d\n", insideCount, outsideCount);
    printf("area : %lf\n", circleAreaApprox(insideCount, outsideCount, r));
}

double actualArea(int r) {
    return M_PI*r*r;
}

void startCalculation(int *insideCount, int *outsideCount, int r, int iteration) {
    double *point = (double *)malloc(2 * sizeof(double));

    for (int i = 0; i < iteration; i++) {
        setPoint(point, r);
        if(insideCircle(point, r)) *insideCount = *insideCount + 1;
        else *outsideCount = *outsideCount + 1;
    }

    free(point);
}

int main (int argc, char **argv) {
    srand(time(NULL));

    int r;
    int iteration;
    int insideCount = 0;
    int outsideCount = 0;

    if (argc == 3) {
        r = atoi(argv[1]);
        iteration = atoi(argv[2]);
    } else {
        printf("Argument are missing\n");
        return 1;
    }

    FILE *p = fopen("area.csv", "a");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    for (int i = 0; i < 10; i++) {
        for (int count = 10; count <= iteration; count *= 10) {
            startCalculation(&insideCount, &outsideCount, r, count);
            // printf("%d, %.3lf, %.3lf\n", count, circleAreaApprox(insideCount, outsideCount, r), actualArea(r));
            fprintf(p, "%d, %.3lf, %.3lf\n", count, circleAreaApprox(insideCount, outsideCount, r), actualArea(r));
            insideCount = 0;
            outsideCount = 0;
        }
    }
    fclose(p);
}