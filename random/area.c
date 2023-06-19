#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
        printf("Argument are missing");
    }

    startCalculation(&insideCount, &outsideCount, r, iteration);
    printResult(insideCount, outsideCount, r);
}