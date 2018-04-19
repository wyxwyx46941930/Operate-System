#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
//约定要求的最大斐波拉契数列的项数为10
#define  MAX_SEQUENCE  10 
typedef  struct{ 
    long  fib_sequence[MAX_SEQUENCE];//存储斐波拉契数列的具体数值
 
    int  sequence_size;//限定子进程生成序列的大小
 
}shared_data;

int main(int argc , char *argv[])
{
    //必须限定程序运行时的操作数为2个
    if(argc != 2)
    {
        printf("Parameter Error\n");
        exit(0);
    }
    //限定所求额斐波拉契数列的最大项数x（0<=x<=10）
    if(atoi(argv[1]) < 0 || atoi(argv[1]) > 10)
    {
        printf("Out of range\n")
        exit(0);
    }
    //创建共享进程编号
    int segment_id ;
    //求出共享内存的内存大小
    int segment_size = sizeof(shared_data);
    //创建共享内存指针
    shared_data *shared_memory ; 
    //分配一个共享内存块
    segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);
    //连接一个共享内存块
    shared_memory = (shared_data *) shmat(segment_id, NULL, 0);
    //把运行程序时输入的参数赋给所申请的共享内存块
    shared_memory -> sequence_size = atoi(argv[1]);
    //判断一下是否共享内存块创建成功
    if(segment_id == -1)
    {
        printf("Create shared memory segment error!\n");
        exit(0);
    }
    else
    {
        printf("Succeed to create the shared memory segment %d\n",segment_id);
    }
    //创建子进程
    int pid;
    pid = fork() ;
    //在子进程中完成对斐波拉契数列的求和
    if(pid == 0)
    {
        //使用指针访问斐波拉契内存块
        shared_memory -> fib_sequence[0] = 0 ;
        shared_memory -> fib_sequence[1] = 1 ;
        if(atoi(argv[1]) > 2)
        {
            for(int i = 2 ; i < atoi(argv[1]) ; i ++ )
            {
                shared_memory ->  fib_sequence[i]  = shared_memory ->  fib_sequence[i - 1]  + shared_memory ->  fib_sequence[i - 2] ; 
            }
        }
    }
    //在父进程中完成对斐波拉契数列的输出
    else
    {
        //父进程中调用wait函数等待程序结束
        wait(0) ;
        printf("The child process finished\n");
        printf("The Fibonacci sequence is:");
        for(int i = 0 ; i < atoi(argv[1]) ; i ++ )
        {
            printf("%d ", shared_memory -> fib_sequence[i] );
        }
        printf("\n");
    }
    //解除内存块的连接
    shmdt(shared_memory);
    //清楚共享内存块
    shmctl(segment_id, IPC_RMID, NULL); 

} 
