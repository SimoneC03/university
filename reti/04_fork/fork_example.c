#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n = 0, pid;

    for (; n < 5; n++)
    {
        printf("n = %d\n", n);
    }

    pid = fork();
    if (pid == 0)
    {
        printf("\n===== CHILD \n n = %d \n", n);
        for (; n < 10; n++)
            printf("pid = %d, n = %d\n", pid, n * 2);
        return 0;
    }
    else
    {
        printf("\n====== FATHER \n n = %d\n", n);
        for (; n < 10; n++)
            printf("pid = %d, n = %d\n", pid, n * 3);
        return 0;
    }
}