#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
 
int main{
    printf("a\n");
    pid_t pid1 = fork();
    if(pid1 == 0 )
    {
        printf("b%d  %d  %d\n",getppid(),getpid(),pid1);
        pid_t pid2= fork();
        if(pid2 == 0)
        {
            printf("c%d  %d  %d\n",getppid(),getpid(),pid2);
        }
    }
    returned 0;
}