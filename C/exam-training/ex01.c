#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
  int k = atoi(argv[1]);
  char w = (argv[2] != NULL) ? argv[2][0] : '-1';
  int N = atoi(argv[3]);
  int M = atoi(argv[4]);
  if (k >= 10 && k <= 15 && w >= 'a' && w <= 'z' && N >= 4 && N <= 8 && M >= 4 && M <= 8)
  {
    char *S[N][M];
    for (int j = 0; j < N; j++)
    {
      for (int i = 0; i < M; i++)
      {
        S[j][i] = "a";
      }
    }

    // printing matrix
    for (int j = 0; j < N; j++)
    {
      for (int i = 0; i < M; i++)
      {
        printf("S[%d][%d] = %s\n", j, i, S[j][i]);
      }
    }
  }
  else
  {
    fprintf(stderr, "%s", "Invalid arguments\n");
  }
}