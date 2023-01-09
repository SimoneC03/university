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

Arguments checkArgs(int, char**);

void main(int argc, char *argv[])
{
  Arguments arguments = checkArgs(argc, argv);
  int j, i;
  char *S[arguments.N][arguments.M];
  for (j = 0; j < arguments.N; j++)
  {
    for (i = 0; i < arguments.M; i++)
    {
      S[j][i] = "a";
    }
  }

  // printing matrix
  for (j = 0; j < arguments.N; j++)
  {
    for (i = 0; i < arguments.M; i++)
    {
      printf("S[%d][%d] = %s\n", j, i, S[j][i]);
    }
  }
}

Arguments checkArgs(int argc, char **argv)
{
  int k = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  char w = (argv[2] != NULL) ? argv[2][0] : '-1';
  int N = (argv[3] != NULL) ? atoi(argv[3]) : -1;
  int M = (argv[4] != NULL) ? atoi(argv[4]) : -1;
  if (k >= 10 && k <= 15 && w >= 'a' && w <= 'z' && N >= 4 && N <= 8 && M >= 4 && M <= 8)
  {
    Arguments arguments = {k, w, N, M};
    return arguments;
  }
  else
  {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}