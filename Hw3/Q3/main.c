#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void leastSquare(int degree, int count, double *x, double *y, float res[10][10]);
double sumOfPow(int count, int pow, double *num);

int main() {
    int i,j,k,n;
    double c,x[10],sum=0.0;
    float A[10][10];
    double res[3];
    double keys[5] = {0, 0.25, 0.5, 0.75, 1.0};
    double values[5] = {1, 1.284, 1.6487, 2.117, 2.7183};


    leastSquare(2, 5, keys, values, A);

    for(i=0;i<3;++i){
        for(j=0;j<4;++j)
            printf("%f ",A[i][j]);
        printf("\n");
    }
    printf("\n");


    for(j=1; j<=n; j++) /* loop for the generation of upper triangular matrix*/
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
    printf("\nThe solution is: \n");
    for(i=1; i<=n; i++)
    {
        printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
    }

    return(0);
}

void leastSquare(int degree, int count, double *x, double *y, float res[10][10]){
    double **factors;
    int i, j;
    double *result;

    result = (double*)calloc(degree+1, sizeof(double));

    factors = (double**)calloc(degree+1, sizeof(double*));
    for(i = 0; i < degree+1; ++i)
        factors[i] = (double*)calloc(degree+2, sizeof(double));

    for(i = 0; i < degree+1; ++i)
        for(j = 0; j < degree+2; ++j)
            factors[i][j] = 0;

    for(i = 0; i <= degree; ++i)
        for(j = 0; j < count; ++j)
            factors[i][degree+1] += (y[j]*pow(x[j],i));

    for(i=0; i <= degree; ++i){
        for(j = 0; j <= degree; ++j){
            factors[i][j] = sumOfPow(count, i+j, x);
        }
    }

    for(i=0; i < degree+1; ++i){
        for(j = 0; j <= degree+1; ++j){
            res[i][j] = (float)factors[i][j];
            printf("%f ",factors[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    free(result);
    for(i = 0; i <= degree; ++i)
        free(factors[i]);
    free(factors);
    return;
}

double sumOfPow(int count, int power, double *num){
    int i;
    double sum = 0;

    for(i = 0; i < count; ++i)
        sum += pow(num[i], power);

    return sum;
}