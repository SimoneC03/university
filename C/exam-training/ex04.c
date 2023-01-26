#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  short int N, M;
  float x, y;
} Arguments;  

Arguments checkArgs(int, char **);
double genDouble(double, double);

double genDouble(double max, double min) {
  double range = (max - min); 
  double div = RAND_MAX / range;
  return min + (rand() / div);
}


Arguments checkArgs(int argc, char **argv) {
  int N = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  int M = (argv[2] != NULL) ? atoi(argv[2]) : -1;
  float x = (argv[3] != NULL) ? atof(argv[3]) : -1;
  float y = (argv[4] != NULL) ? atof(argv[4]) : -1;
  if (N >= 20 && N <= 25 && M >= 10 && M <= 15 && x > 5 && x < 10 && y > 40 && y < 50) {
    Arguments arguments = {N, x, y};
    printf("\nInsert: %d for N, %d for M, %f for x and %f for y\n\n", arguments.N, arguments.M, arguments.x, arguments.y);
    return arguments;
  }
  else {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}


void main(int argc, char *argv[]) {
  Arguments arguments = checkArgs(argc, argv);
  int N = arguments.N, M = arguments.M;
  float x = arguments.x, y = arguments.y;
}