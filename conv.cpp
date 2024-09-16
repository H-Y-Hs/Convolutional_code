#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <string.h>
//void 
void printH(int **H, int r, int n);
void printA(int **A, int r, int k);
using namespace std;
int main()
{
    int L;
    int m = 6;
    int j = 0;         
	char simm[100];
    // read file
    FILE *in;
    in = fopen("Sim.txt", "r");
    if (in == NULL) {
        printf("failed to open the file.\n");
        return 1;
    }
    //read L
    fscanf(in, "%d\n", &L);
    fgets(simm,100,in);
    
	int *l = (int *)malloc((L + m) * sizeof(int));
	int x[63] = {0};
    int i;
    int input[L + m];
    l[0] = 1;
    for (int i = 1; i < 6; i++)
    {
        l[i] = 0;
    }
    for (int i = 6; i < L + m; i++)
    {
        l[i] = (l[i - m] + l[i - m + 1]) % 2;
    }
    
    printf("l:\n");
    for (int i = 0; i < L ; i++)
	{
		printf("%d ", l[i]);
	}
    printf("\n");
	
    
    
    
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

    for(int i = 0; i < (L + m) ; i++)
    {
    	if(i < L)
    		input[i] = l[i];
    	else if(i >= L)
    		input[i] = 0;
	}
	printf("L + m :\n");
    for (int i = 0; i < (L + m) ; i++)
    {
        printf("%d ", input[i]);
    }
    printf("\n\n");
	
	int convG1[L + m + 6] = {0};
    for (int i = 0; i < L + m; i++) {
        for (int j = 0; j < 7; j++) {
            if (i + j < L + m) {
                convG1[i + j] ^= input[i] * G1[j];
            }
        }
    }

    printf("Convolution of L+m with G1:\n");
    for (int i = 0; i < L + m ; i++) {
        printf("%d ", convG1[i]);
    }
    printf("\n\n");
    
    int convG2[L + m + 6] = {0};
    for (int i = 0; i < L + m; i++) {
        for (int j = 0; j < 7; j++) {
            if (i + j < L + m) {
                convG2[i + j] ^= input[i] * G2[j];
            }
        }
    }

    printf("Convolution of L+m with G2:\n");
    for (int i = 0; i < L + m ; i++) {
        printf("%d ", convG2[i]);
    }
    printf("\n\n");
    
    
   

    int *pre = (int*)malloc((2 * (L + m)) * sizeof(int));
    int *ans = (int*)malloc((2 * (L + m)) * sizeof(int));
		
	for (int i = 0; i < L + m; i++)
	{
	    pre[j] = convG1[i];
	    j++;          
	    pre[j] = convG2[i];
	    j++;        
	}
    printf("pre:\n");
    for (int i = 0; i < 2*(L + m); i++)
    {
        printf("%d ", pre[i]);
    }
    printf("\n\n");
    printf("ans:\n");
    for (int i = 0; i < 2 * (L + m) ; i++) 
	{
    	ans[i] = (pre[i] == 0) ? 1 : -1;
    	printf("%d ", ans[i]);
    }
    
    //store file
    FILE *out;
    out = fopen("x.txt" , "w");
    for (int i = 0 ; i < 2 * (L + m) ; i++)
    {
    	fprintf(out , "%d " , ans[i]);            
    } 
    return 0;
}
