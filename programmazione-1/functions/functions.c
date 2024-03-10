#include <stdio.h>
#include <stdlib.h>

void log(double);

void log(double n) {
  printf("%f\n", n);
}

void absolute(double *);

void absolute(double *n) {
  *n = abs(*n);
}
void main() {
  log((double)34);
  double negativeNumber = -44;
  printf("%f\n", negativeNumber);
  absolute(&negativeNumber);
  printf("%f\n", negativeNumber);
}