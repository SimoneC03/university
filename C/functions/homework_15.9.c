#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double absDiagonalsDifference(int c, int v[][c]);

double absDiagonalsDifference(int c, int v[][c])
{
  int primSum = 0;
  int secSum = 0;
  for(int i = 0; i<c; i++) {
    for(int j = 0; j<c; j++) {
      if(i==j) {
        primSum += v[i][j];
      }
      if(i+j == (c-1)) {
        secSum += v[i][j];
      }
    }
  }
  double av1 = (double)primSum / (double)c;
  double av2 = (double)secSum / (double)c;
  return fabs(av1 - av2);
}

void main()
{
  int r;
  printf("Insert the rows and columns number of the qudratic matrix: \n");
  scanf("%d", &r);
  printf("Fill the quadratic matrix: \n");
  int matrix[r][r];
  // fill the matrix
  for (int i = 0; i<r; i++) {
    for(int j = 0; j<r; j++) {
      printf("matrix[%d][%d] = ",i,j);
      scanf("%d", &matrix[i][j]);
    }
  }
  // print the matrix
  for (int i = 0; i<r; i++) {
    for(int j = 0; j<r; j++) {
      if(j+1 == r) {
        printf(" %d |\n", matrix[i][j]);
      }
      else if(j==0) {
        printf("| %d ", matrix[i][j]);
      }
      else {
        printf(" %d ", matrix[i][j]);
      }
    }
  }
  // calculate the diagonals difference
  double difference = absDiagonalsDifference(r, matrix);
  printf("The difference between the primary and the secondary diagonal's values average is: %f\n", difference);
}