#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
  int k = atoi(argv[1]);
  char w = argv[2][0];
  int N = atoi(argv[3]);
  int M = atoi(argv[4]);
  if(k >= 10 && k <= 15 && w >= 'a' && w <= 'z' && N >= 4 && N <= 8 && M >= 4 && M <= 8) {
    // wip
  }
  else {
    fprintf(stderr, "%s", "Invalid arguments\n");
  }
}