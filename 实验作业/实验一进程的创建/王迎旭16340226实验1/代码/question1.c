#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main() {
    int pid1 = fork();
    printf("**1**%d  %d  %d\n",getppid(),getpid(),pid1);
    int pid2 = fork();
    printf("**2**%d  %d  %d\n",getppid(),getpid(),pid2);
    if (pid1 == 0) {
        int pid3 = fork();
        printf("**3**%d  %d  %d\n",getppid(),getpid(),pid3);
    }
    else
        printf("**4**\n");
    return 0;
}