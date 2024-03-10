#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  short int N;
  float x, y;
} Arguments;  

Arguments checkArgs(int, char **);
double genDouble(double, double);
double **allocateMatrix(int, float, float);
void printMatrix(double **, int);
double *puntoC(double **, int, int *);
void sortArray(double *, int);
void printArray(double *, int);

void printArray(double *arr, int length) {
  int i;
  double sum;
  printf("\nSorted Array:\n");
  for(i = 0; i < length; i++) {
    printf("arr[%d] = %lf\n", i, arr[i]);
    sum += arr[i];
  }
  printf("\nThe mathematical mean of the array is %lf\n", sum/length);
}

void sortArray(double *arr, int length) {
  int i, j;
  for(i = 0; i < length; i++)
    for(j = 0; j < length - 1 - i; j++)
      if(arr[j]> arr[j+1]) {
        double temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
      } 
}

double *puntoC(double **matrix, int N, int *totalValues) {
  double minp = 0; // main diagonal minimum
  double maxd = 0; // secondary diagonal maximum
  int i, j;
  int c = 0;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++) {
      if(i == j && matrix[i][j] < minp) {
        minp = matrix[i][j];
      } else if((i+j) == (N-1) && matrix[i][j] > maxd) {
        maxd = matrix[i][j];
      }
    }
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      if(matrix[i][j] >= minp && matrix[i][j] <= maxd)
        c++;
  double *arr = malloc(sizeof(double) * c);
  *totalValues = c;
  int k = 0;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      if(matrix[i][j] >= minp && matrix[i][j] <= maxd) {
        arr[k] = matrix[i][j];
        k++;
      }
  return arr;
}

void printMatrix(double **matrix, int N) {
  int i, j;
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      printf("A[%d][%d] = %lf\n", i, j, matrix[i][j]);
}

double genDouble(double max, double min) {
  double range = (max - min); 
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

double **allocateMatrix(int N, float x, float y) {
  double **matrix = malloc(sizeof(double *) * N);
  int i, j;
  for(i = 0; i < N; i++) {
    matrix[i] = malloc(sizeof(double) * N);
    for(j = 0; j < N; j++)
      matrix[i][j] = genDouble(y, x);
  }
  return matrix;
}

Arguments checkArgs(int argc, char **argv) {
  int N = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  float x = (argv[2] != NULL) ? atof(argv[2]) : -1;
  float y = (argv[3] != NULL) ? atof(argv[3]) : -1;
  if (N >= 10 && N <= 20 && x > 5 && x < y && y < 30) {
    Arguments arguments = {N, x, y};
    printf("\nInsert: %d for N, %f for x and %f for y for w\n\n", arguments.N, arguments.x, arguments.y);
    return arguments;
  }
  else {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}


void main(int argc, char *argv[]) {
  Arguments arguments = checkArgs(argc, argv);
  int N = arguments.N;
  float x = arguments.x, y = arguments.y;
  double **A = allocateMatrix(N, x, y);
  int totalValues = 0;
  double *arr = puntoC(A, N, &totalValues);
  printf("C answer: %d\n", totalValues);
  sortArray(arr, totalValues);
  printArray(arr, totalValues);
}