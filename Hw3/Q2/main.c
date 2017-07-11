
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findPol(int count, double *x, double *y);
double help(int count, double *x, double *y);

int main() {
    double x[3], y[3];
    x[0] = 8.1;
    y[0] = 16.9441;
    x[1] = 8.3;
    y[1] = 17.56492;
    x[2] = 8.6;
    y[2] = 18.50315;
    findPol(3, x, y);
    return 0;
}

void findPol(int count, double *x, double *y){
    double **factors, f[2];
    double *tmpX, *tmpY, res;
    int i, j;


    factors = (double**)calloc(count-1,sizeof(double*));
    for(i = 0; i < count-1; ++i)
        factors[i] = (double*)calloc(count+1, sizeof(double));

    for (i = 0; i < count-1; ++i)
        for (j = 0; j < count+1; ++j)
            factors[i][j] = 0;


    factors[0][0] = -x[0];
    factors[0][1] = 1;// (x-1) oldu

    for(i = 1; i < count-1; ++i){
        f[0] = -x[i];
        f[1] = 1; //(X-Xi) tutuyo

        for(j = 0; j < count + 1; ++j){
            factors[i][j] += factors[i-1][j]*f[0];
            factors[i][j+1] += factors[i-1][j]*f[1];
        }

    }

    for(i = 2; i <= count; ++i){
        tmpX = (double*)calloc(i, sizeof(double));
        tmpY = (double*)calloc(i, sizeof(double));

        for(j = 0; j < i; ++j){
            tmpX[j] = x[j];
            tmpY[j] = y[j];
        }
        printf("\n");

        res = help(i, tmpX, tmpY);

        for(j = 0; j <= i; ++j){
            factors[i-2][j] *= res;
        }
        free(tmpX);
        free(tmpY);
    }


    factors[0][0] += y[0];
    for(i = 1; i < count-1; ++i){
        for(j = 0; j < i + 2; ++j){
            factors[i][j] += factors[i-1][j];
        }
    }

    for(i = 0; i < count-1; ++i){
        for(j = count-1; j >= 0; --j){
            printf("%f ", factors[i][j]);
        }
        printf("\n");
    }

    for(i = count-1; i >= 0; --i){
        printf("%f", factors[count-2][i]);

        if(i>0){
            printf("*X");
            if(i > 1)
                printf("^%d",i);
            printf(" + ");
        }
    }

    for(i = 0; i < count; ++i)
        free(factors[i]);
    free(factors);

    return;
}

double help(int count, double *x, double *y){
    if(count > 2){
        double *tmpX, *tmpY, res1, res2;
        int i;
        tmpX = (double*)calloc(count-1, sizeof(double));
        tmpY = (double*)calloc(count-1, sizeof(double));

        for(i = 0; i < count-1; ++i){
            tmpX[i] = x[i+1];
            tmpY[i] = y[i+1];
        }
        res1 = help(count-1, tmpX, tmpY);
        for(i = 0; i < count-1; ++i){
            tmpX[i] = x[i];
            tmpY[i] = y[i];
        }
        res2 = help(count-1, tmpX, tmpY);
        free(tmpX);
        free(tmpY);

        return ((res1-res2) / (x[count-1] - x[0]));
    }
    else if(count == 2){
        return ((y[1]-y[0]) / (x[1]-x[0]));
    }
}