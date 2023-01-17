#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int k;
  char w;
  int N;
  int M;
} Arguments;

Arguments checkArgs(int, char **);
char* genString(int, char, char);

void main(int argc, char *argv[])
{
  Arguments arguments = checkArgs(argc, argv);
  int M = arguments.M, N = arguments.N, K = arguments.k;
  int j, i;
  char ***S = malloc(M * sizeof(char **));

  for (j = 0; j < M; j++)
  {
    S[j] = malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
    {
      S[j][i] = malloc(sizeof(char) * K);
      char *randomStr = genString(K, 'a', 'z');
      strcpy(S[j][i], randomStr);
    }
  }

  // printing matrix
  for (j = 0; j < M; j++)
  {
    for (i = 0; i < N; i++)
      printf("%s\n", S[j][i]);
    printf("\n");
  }

  // free memory
  for (j = 0; j < M; j++)
    for (i = 0; i < N; i++)
      free(S[j][i]);
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
    printf("Insert: %d for k, %c for w, %d for N and %d for M", arguments.k, arguments.w, arguments.N, arguments.M);
    return arguments;
  }
  else
  {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}

char* genString(int length, char start, char end) {
  char* str = malloc(sizeof(char)*length);
  int i;
  int st = (int)(start);
  int en = (int)(end);
  for(i = 0; i < length; i++)
    str[i] = (rand()%(en-st))+st;
  return str;
}