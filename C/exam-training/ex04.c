#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  short int N, M;
  float x, y;
} Arguments;  

Arguments checkArgs(int, char **);
double genDouble(double, double);
void push(double[], double, int *, int);
double pop(double[], int *);
void printStack(double[], int);

void printStack(double arr[], int length) {
  for(int i = 0; i < length; i++) 
    printf("stack[%d] = %lf\n", i, arr[i]);
}

double pop(double arr[], int *counter) {
  if(*counter < 0) {
    printf("Stack is empty.");
    return -1;
  }
  int i = *counter;
  double temp = arr[i];
  arr[i] = 0;
  *counter -= 1;
  return temp;
}

void push(double arr[], double value, int *counter, int length) {
  *counter += 1;
  int i = *counter; 
  if(i >= length - 1) {
    printf("Stack is full. Cannot insert %lf", value);
    return;
  }
  arr[i] = value;
}

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
  int length = N/2;
  double stack[length];
  int counter = -1;
  push(stack, genDouble(y, x), &counter, length);
  push(stack, genDouble(y, x), &counter, length);
  push(stack, genDouble(y, x), &counter, length);
  push(stack, genDouble(y, x), &counter, length);
  push(stack, genDouble(y, x), &counter, length);
  printf("%lf removed from the stack", pop(stack, &counter));
  printStack(stack, length);
}