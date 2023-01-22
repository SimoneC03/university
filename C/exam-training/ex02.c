#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int N;
  char w;
} Arguments;

Arguments checkArgs(int, char **);
char *genString(int, char, char);

void main(int argc, char *argv[])
{
  Arguments arguments = checkArgs(argc, argv);
  int N = arguments.N;
  char w = arguments.w;
  
}

Arguments checkArgs(int argc, char **argv)
{
  int N = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  char w = (argv[2] != NULL) ? argv[2][0] : '-1';

  if (N >= 10 && N <= 20 && w >= 'a' && w <= 'z')
  {
    Arguments arguments = {N, w};
    printf("\nInsert: %d for k, '%c' for w, %d for N and %d for M\n\n", arguments.N, arguments.w);
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
