#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>
#define RADIUS 7
#define DEBUG 0

int main(int argc, char *argv[]){

    if(argc != 2){              
        puts("Parameter Error");
        return 0;
    }

    int N = atoi(argv[1]);    
    double x, y;
    int in, out;
    int i;
    long double resofArea, resofRealArea, gosa;
    
    in  = 0;
    out = 0;
    srand((unsigned int)time(NULL));

    for(i = 0; i < N; i++){
        x = ((float)rand()/(float)(RAND_MAX)) * RADIUS;
        y = ((float)rand()/(float)(RAND_MAX)) * RADIUS;

        if(x * x + y * y <= RADIUS*RADIUS) {
            in+=1;
        } else {
            out+=1;
        }
    }

    resofArea = (long double)(196*in) / (long double)(in+out);
    resofRealArea = 49.0 * M_PI;
    gosa = fabs(resofArea - resofRealArea);
    printf("%d %Lf %Lf\n", N, resofArea, gosa);
    return 0;
}
