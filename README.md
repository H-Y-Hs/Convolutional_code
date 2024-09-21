# Convolutional_code
Project of Error control coding - Convolutional code

##Block Diagram
![Block Diagram](https://github.com/H-Y-Hs/Convolutional_code/blob/main/Block_Diagram_of_Convolutional_code.jpg?raw=true)

##Pseudo code
```c
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

main ()
{
  ...
  long *idum;
  idum = (long *)malloc(sizeof(long));
  *idum = SEED; //SEED must be a negative integer.
  ...
  ...
}
```

###Use **normal()** to output two independent normal random variables, $n_1$ and $n_2$
![normal()](https://github.com/H-Y-Hs/Convolutional_code/blob/main/normal.jpg?raw=true)

####Use **ran1()** to generate a random variable uniformly distributed in the interval (0, 1).
```c
ran1(long *idum)
{
  int j;
  long k;
  static long iy=O;
  static long iv[NTAB];
  double temp;
  if (*idum <= 0 || !iy){
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    for (j=NTAB+7;j>=0;j--){
      k= (*idum) / IQ;
      *idum=IA*(*idum-k*IQ)-IR*k;
      if (*idum < 0) *idum += IM;
      if (j<NTAB) iv[j]=*idum;
    }
  iy=iv[0];
  }
  k= (*idum) / IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if (*idum < 0) *idum += IM;
  j=iy/NDIV;
  iy=iv[j];
  iv[j] = *idum;
  if ((temp=AM*iy) > RNMX) return RNMX,
  else return temp;
}
```

#####Input Sim.txt
![normal()](https://github.com/H-Y-Hs/Convolutional_code/blob/main/Sim.txt.jpg?raw=true)

######Notes
1.  Use Best-state method
2.  Truncated window length = 32
