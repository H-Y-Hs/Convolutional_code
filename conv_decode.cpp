#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
#define R 0.5
long static *idum;
double ran1() //0~1 uniform random variable
{
 int j;
 long k;
 static long iy = 0;
 static long iv[NTAB];
 double temp;
 if (*idum <= 0 || !iy) 
 {
  if (-(*idum) < 1) 
   *idum = 1; 
  else 
   *idum = -(*idum);
  for (j = NTAB + 7 ; j >= 0 ; j --) 
  {
   k = (*idum) / IQ;
   *idum = IA * (*idum - k * IQ) - IR * k;
   if (*idum < 0) 
    *idum += IM;
   if (j < NTAB) 
    iv[j] = *idum;
  }
  iy = iv[0];
    }
 k = (*idum) / IQ; 
 *idum = IA * (*idum - k * IQ) - IR * k; 
 if (*idum < 0) 
  *idum += IM;
 j = iy / NDIV; 
 iy = iv[j]; 
 iv[j] = *idum;
 if ((temp = AM * iy) > RNMX) 
  return RNMX;
 else 
  return temp;
}
//void 
void normal(double *n , double sigma)
{
    double x1 , x2 , s;
    long idum;
    do
    {
     x1 = ran1();
     x2 = ran1();
     x1 = 2.0 * x1 - 1.0;
     x2 = 2.0 * x2 - 1.0;
     s = pow(x1 , 2) + pow(x2 , 2);
    } while (s >= 1.0);
     n[0] =  sigma * x1 * pow((-2) * log(s)/s , 0.5);
     n[1] =  sigma * x2 * pow((-2) * log(s)/s , 0.5);
}

int main()
{
	int N, L, SEED, D;
	double SNR;	       
	char simm[100];
    // read file
    FILE *in;
    in = fopen("Sim.txt", "r");
    if (in == NULL) {
        printf("failed to open the file.\n");
        return 1;
    }
    //read L    
    fscanf(in, "%d\n", &N);
    fgets(simm,100,in);
    fscanf(in, "%d\n", &L);
    fgets(simm,100,in);
    fscanf(in, "%lf\n", &SNR);
    fgets(simm,100,in);
    fscanf(in, "%d\n", &SEED);
    fgets(simm,100,in);
    fscanf(in, "%d\n", &D);
    fgets(simm,100,in);
    printf("N = %d\n", N);
    printf("L = %d\n", L);
    printf("SNR = %.1lf\n", SNR);
    printf("SEED = %d\n", SEED);
    printf("D = %d\n", D);
	
	double sigma;
	double SNR_num;
	double sigma2;
	int m = 6;
    int j = 0;         
	int *l = (int *)malloc((N + m) * sizeof(int));
	int x[63] = {0};
    int i;
    int input[N + m];
    l[0] = 1;
    for (int i = 1; i < 6; i++)
    {
        l[i] = 0;
    }
    for (int i = 6; i < N + m; i++)
    {
        l[i] = (l[i - m] + l[i - m + 1]) % 2;
    }
    
    printf("l:\n");
    for (int i = 0; i < N ; i++)
	{
		printf("%d ", l[i]);
	}
    printf("\n");
	//©w¸qG1 G2 
	int G1[] = {1, 0, 1, 1, 0, 1, 1};
    printf("G1:\n");
    for (int i = 0; i < 7; i++) {
        printf("%d ", G1[i]);
    }
    printf("\n");
    int G2[] = {1, 1, 1, 1, 0, 0, 1};
    printf("G2:\n");
    for (int i = 0; i < 7; i++) {
        printf("%d ", G2[i]);
    }
    printf("\n");
	//¸É 0 
    for(int i = 0; i < (N + m) ; i++)
    {
    	if(i < N)
    		input[i] = l[i];
    	else if(i >= N)
    		input[i] = 0;
	}
	printf("N + m :\n");
    for (int i = 0; i < (N + m) ; i++)
    {
        printf("%d ", input[i]);
    }
    printf("\n\n");
	//Convolution 
	int convG1[N + m + 6] = {0};
	int *modulate1 = (int *)malloc((N + m) * sizeof(int));
    for (int i = 0; i < N + m; i++) {
        for (int j = 0; j < 7; j++) {
            if (i + j < N + m) {
                convG1[i + j] ^= input[i] * G1[j];
            }
        }
    }
    printf("Convolution of N+m with G1:\n");
    for (int i = 0; i < N + m ; i++) {
        printf("%d ", convG1[i]);
    }
    printf("\n\n");
    
    int convG2[N + m + 6] = {0};
    int *modulate2 = (int *)malloc((N + m) * sizeof(int));
    for (int i = 0; i < N + m; i++) {
        for (int j = 0; j < 7; j++) {
            if (i + j < N + m) {
                convG2[i + j] ^= input[i] * G2[j];
            }
        }
    }

    printf("Convolution of N+m with G2:\n");
    for (int i = 0; i < N + m ; i++) 
	{
        printf("%d ", convG2[i]);
    }
    printf("\n\n");
    //Modulate
	printf("modulate1:\n"); 
    for (int i = 0; i < (N + m) ; i++) 
	{
    	modulate1[i] = (convG1[i] == 0) ? 1 : -1;
    	printf("%d ", modulate1[i]);
    }
    printf("\n\n");
    
    
    printf("modulate2:\n"); 
    for (int i = 0; i < (N + m) ; i++) 
	{
    	modulate2[i] = (convG2[i] == 0) ? 1 : -1;
    	printf("%d ", modulate2[i]);
    }      
    
    SNR_num = pow(10, SNR/10);
	sigma2 = pow (2 * SNR_num * R ,-1);
	printf("\n\nsigma2 = %lf\n", sigma2);
	sigma = sqrt(sigma2);
	printf("sigma = %lf\n", sigma);
	
	idum = (long *)malloc(sizeof(long));
	*idum = SEED; //SEED must be a negative integer
	//Add noise    
    double noise[2] = {0};
    double *y1 = (double *)malloc((N + m) * sizeof(double));
    double *y2 = (double *)malloc((N + m) * sizeof(double));
    for (int i = 0; i < (N + m); i++)
    {
       	normal(noise, sigma);
    	y1[i] = modulate1[i] + noise[0];    	
		y2[i] = modulate2[i] + noise[1];
	}

	printf("y1:\n");
    for (int i = 0; i < N + m ; i++) 
	{
        printf("%lf ", y1[i]);
    }
    printf("\n\n");
    printf("y2:\n");
    for (int i = 0; i < N + m ; i++) 
	{
        printf("%lf ", y2[i]);
    }
    printf("\n\n");
    
    //±Æ¦C 
	double *y = (double*)malloc((2 * (N + m)) * sizeof(double));	
	for (int i = 0; i < N + m; i++)
	{
	    y[j] = y1[i];
	    j++;          
	    y[j] = y2[i];
	    j++;        
	}
    printf("y:\n");
    for (int i = 0; i < 2*(N + m); i++)
    {
        printf("%lf ", y[i]);
    }
    printf("\n\n");   
    
    int *hard = (int *)malloc(2*(N + m) * sizeof(int));
    printf("hard:\n");
    for (int i = 0; i < 2 * (N + m); i++)
    {
    	if (y[i] >= 0)
    	hard[i] = 0;
    	else
    	hard[i] = 1;
	}
	for (int i = 0; i < 2* (N + m); i++)
    {
    	printf("%d " ,hard[i]); 
	}
	printf("\n\n");
	
	int **arr = (int**)malloc(128 * sizeof(int*));
	for (int i = 0; i < 128; i++)
	{
	    arr[i] = (int*)malloc(7 * sizeof(int));
	    arr[i][0] = (i % 2 == 0) ? 0 : 1;
	    for (int j = 6; j >= 1; j--)
	    {
	        arr[i][j] = (i >> (6-j)) & 1 ? '1' : '0';
	    }
	    arr[i][6] = '\0';
	}
	
	for (int i = 0; i < 128; i++)
	{
	    for (int j = 0; j < 7; j++)
	    {
	        printf("%c ", arr[i][j]);
	    }
	    printf("\n");
	}
    return 0;
}
