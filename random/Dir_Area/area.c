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

void startCalculation(int *insideCount, int *outsideCount, int r, int maxIteration) {
    double *point = (double *)malloc(2 * sizeof(double));

    for (int i = 0; i < maxIteration; i++) {
        setPoint(point, r);
        if(insideCircle(point, r)) *insideCount = *insideCount + 1;
        else *outsideCount = *outsideCount + 1;
    }

    free(point);
}

void resetValue(int *inside, int *outside) {
    *inside = 0;
    *outside = 0;
}

double errorPercentage(double error, int r) {
    return (error / actualArea(r)) * 100;
}

int main (int argc, char **argv) {
    srand(time(NULL));

    int r;
    int maxIteration;
    int insideCount = 0;
    int outsideCount = 0;
    const int repetitionCount = 3;

    if (argc == 3) {
        r = atoi(argv[1]);
        maxIteration = atoi(argv[2]);
    } else {
        printf("Argument are missing\n");
        return 1;
    }

    char filename[20];
    sprintf(filename, "area%d.csv", r);
    printf("%s\n", filename);

    FILE *p = fopen(filename, "w");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    const int increment = (int)log10(maxIteration);
    double *area = (double *)malloc(increment * repetitionCount * sizeof(double));
    double *error = (double *)malloc(repetitionCount * sizeof(double));

    double *q = area;
    for (int i = 0; i < repetitionCount; i++) {
        for (int count = 10; count <= maxIteration; count *= 10) {
            startCalculation(&insideCount, &outsideCount, r, count);
            *q = circleAreaApprox(insideCount, outsideCount, r);
            q++;
            resetValue(&insideCount, &outsideCount);
        }
    }

    printf("Sample Count, Actual, Result_1, Error_1,  Error_1,");
    printf("Result_2, Error_2, Error_2, ");
    printf("Result_3, Error_3, Error_3, \n");

    fprintf(p, "Sample Count, Actual, Result_1, Error_1,  Error_1,");
    fprintf(p, "Result_2, Error_2, Error_2, ");
    fprintf(p, "Result_3, Error_3, Error_3, \n");

    for (int i = 0; i < increment; i++) {
        printf("%d, %.3lf, ", (int)pow(10, i + 1), actualArea(r));
        fprintf(p, "%d, %.3lf, ", (int)pow(10, i + 1), actualArea(r));
        for (int j = 0; j < repetitionCount; j++) {
            error[j] = area[i + j*increment] - actualArea(r);
            printf("%.3lf, %.3lf, %.3lf%%, ", area[i + j*increment], fabs(errorPercentage(error[j], r)), fabs(errorPercentage(error[j], r)));
            fprintf(p, "%.3lf, %.3lf, %.3lf%%, ", area[i + j*increment], fabs(errorPercentage(error[j], r)), fabs(errorPercentage(error[j], r)));
        }
        printf("\n");
        fprintf(p, "\n");
    }

    free(area);
    free(error);
    fclose(p);
}