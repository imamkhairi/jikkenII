#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>
#define RADIUS 1
#define DEBUG 0

double f(double* x, double* y);
int infunction(double x, double y);

int main(int argc, char *argv[]){

    if(argc != 2){              
        puts("Parameter Error");
        return 0;
    }

    int N = atoi(argv[1]);

    double x[N];
    double y[N];
    double pi, gosa;
    int in, out;
    int i;
    
    pi = 0;
    in  = 0;
    out = 0;
    srand((unsigned int)time(NULL));

    for(i = 0; i < N; i++){
        f(&x[i], &y[i]);
        if(infunction(x[i], y[i]) == 1){
            in+=1;
        } else {
            out+=1;
        }
    }

#if DEBUG == 1
    printf("%d %d", in, out);
#endif

    pi = 4.0 * ((double)in / ((double)in + (double)out));
    gosa = fabs(M_PI - pi);
    printf("%d %f %e\n", N, pi, gosa);
 

    return 0;
}

double f(double* x, double* y){
    *x = ((float)rand()/(float)(RAND_MAX)) * RADIUS;
    *y = ((float)rand()/(float)(RAND_MAX)) * RADIUS;
}

int infunction(double x, double y){
    if ((x*x + y*y) <= RADIUS) {
        return 1;
    } else {
        return 0;
    }
}