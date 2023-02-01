#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  short int k;
  char w;
  short int N;
  short int M;
} Arguments;

Arguments checkArgs(int, char **);
char *genString(int, char, char);
char ***allocateMatrix(int, int, int);
void fillMatrix(char ***, int, int, int);
void sortMatrix(char ***, int, int);
void sortStrings(char **, int);
void printMatrix(char ***, int, int);
char *searchWString(char ***, int, int, int, char, int *, int *);
void replaceChar(char *, char, char);

void main(int argc, char *argv[])
{
  Arguments arguments = checkArgs(argc, argv);
  int M = arguments.M, N = arguments.N, K = arguments.k;
  char w = arguments.w;
  int i, j;
  int rowIndex = 0, colIndex = 0;
  char ***S = allocateMatrix(M, N, K);
  fillMatrix(S, M, N, K);
  sortMatrix(S, M, N);
  printMatrix(S, M, N);
  
  char *string = searchWString(S, M, N, K, w, &rowIndex, &colIndex);
  replaceChar(string, '*', w);
  printf("\nThe string with most \"%c\" occurrencies is at S[%d][%d]: \"%s\"\n\n", w, rowIndex, colIndex, string);

  // free memory
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      free(S[i][j]);
}

Arguments checkArgs(int argc, char **argv)
{
  int k = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  char w = (argv[2] != NULL) ? argv[2][0] : '-1';
  int M = (argv[3] != NULL) ? atoi(argv[3]) : -1;
  int N = (argv[4] != NULL) ? atoi(argv[4]) : -1;

  if (k >= 10 && k <= 15 && w >= 'a' && w <= 'z' && N >= 4 && N <= 8 && M >= 4 && M <= 8)
  {
    Arguments arguments = {k, w, N, M};
    printf("\nInsert: %d for k, '%c' for w, %d for N and %d for M\n\n", arguments.k, arguments.w, arguments.N, arguments.M);
    return arguments;
  }
  else
  {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}

char *genString(int length, char start, char end)
{
  char *str = malloc(sizeof(char) * length);
  int i;
  int st = (int)(start);
  int en = ((int)(end)) + 1;
  for (i = 0; i < length; i++)
    str[i] = (rand() % (en - st)) + st;
  return str;
}

char ***allocateMatrix(int M, int N, int K)
{
  int i, j;
  char ***matrix = malloc(M * sizeof(char **));
  for (i = 0; i < M; i++)
  {
    matrix[i] = malloc(N * sizeof(char *));
    for (j = 0; j < N; j++)
    {
      matrix[i][j] = malloc(sizeof(char) * K);
    }
  }
  return matrix;
}

void fillMatrix(char ***matrix, int M, int N, int K)
{
  int i, j;
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < N; j++)
    {
      char *randomStr = genString(K, 'a', 'z');
      strcpy(matrix[i][j], randomStr);
    }
  }
}

void sortMatrix(char ***matrix, int M, int N)
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M - 1 - i; j++)
      if (strcmp(matrix[j + 1][i], matrix[j][i]) < 0)
      {
        char *temp = matrix[j][i];
        matrix[j][i] = matrix[j + 1][i];
        matrix[j + 1][i] = temp;
      }
  }
}


void printMatrix(char ***matrix, int M, int N)
{
  int i, j;
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < N; j++)
      printf("%s - ", matrix[i][j]);
    printf("\n");
  }
}

char *searchWString(char ***matrix, int M, int N, int K, char w, int *rowIndex, int *colIndex) {
  char *stringWithMostW;
  int wMostOccurrencies = 0;
  int i, j, k;
  for(i = 0; i < M; i++)
    for(j = 0; j < N; j++) {
      int c = 0;
      for(k = 0; k < K; k++) {
        if(matrix[i][j][k] == w) {
          c++;
        }
      }
      if(c > wMostOccurrencies) {
        wMostOccurrencies = c;
        stringWithMostW = matrix[i][j];
        *rowIndex = i;
        *colIndex = j;
      }
    }
  return stringWithMostW;
}

void replaceChar(char *string, char c, char toReplace) {
  int i = 0;
  int length = strlen(string);
  while (i < length)
  {
    if(string[i] == toReplace) {
      string[i] = c;
    } 
    i++;
  }
  
}