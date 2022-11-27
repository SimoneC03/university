#include <stdio.h>

int main()
{
  int num = 200;
  int *num_P = &num;
  printf("int num = 200\n");
  printf("num value: %d \n", num);
  printf("num pointer address: %p \n", num_P);
  printf("num pointer value: %d \n\n", *num_P);

  double v[] = {21,3,4,2,453.24};
  double *v_P = v;
  printf("v[] = {21,3,4,2,453.24}\n");
  printf("v[] first value: %f \n", v[0]);
  printf("v[] first value using pointer: %f \n", *v_P);
  printf("v[] second value: %f \n", v[1]);
  printf("v[] second value using pointer: %f \n", *(v_P+1));

  return 0;
} 