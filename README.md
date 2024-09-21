# Convolutional_code
Project of course in master degree - Convolutional code

##Block Diagram
![Block Diagram](https://github.com/H-Y-Hs/Convolutional_code/blob/main/Block_Diagram_of_Convolutional_code.jpg?raw=true)

Pseudo code
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
