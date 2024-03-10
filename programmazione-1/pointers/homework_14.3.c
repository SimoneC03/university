#include <stdio.h>
#include <stdlib.h>

int main()
{
  int N = 200;
  double v[N];
  double * const ptr = v;
  const double *ptrCon = v;
  printf("v[] values\n");
  // Initialize V elements with pseudo-random numbers
  for(int i=0; i<N; i++) {
    v[i] = (rand()+10) % 50;
    printf("v[%d] = %f\n", i, v[i]);
  }
  printf("\n");
  for(int i=0; i<N; i++) {
    // Print only if i is not a multiple of 2 or 3
    if(i % 2 != 0 && i % 3 != 0) {
      printf("v[%d] = %f\n", i, *(ptr+i));
      // Changing value to 100-200 random value
      v[i] = (rand()+100) % 200;
    }
  }
  printf("\n");
  for(int i=0; i<N; i++) {
    printf("v[%d] = %f\n", i, *(ptrCon+i));
  }
} 