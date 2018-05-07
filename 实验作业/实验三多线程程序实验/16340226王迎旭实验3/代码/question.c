#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int number = 0 ;//定义全局变量

void * func(void *data)
{
    int *a = (int *) data ;
    for( int i = 2 ; i < number ; i ++ )
    {
        a[i] = a[i - 1] + a [i - 2] ;
    }
    pthread_exit(NULL);
}

int main()
{
	while(1)
	{
    	printf("Number:");
    	scanf("%d",&number) ;
    	if( number > 2)
    	{
    		break ;
    	}
    	else
    	{
    		printf("Number error\n");
    	}
    }
    int *a = (int*)malloc(sizeof(int) * 100) ;
    a[0] = 0 ;
    a[1] = 1 ;
    //创建线程指针
    pthread_t th ;
    //创建线程
    pthread_create(&th,NULL,func,(void*)a);
    //
    pthread_join(th,NULL);
    //完成输出
    printf("Fibonacci:");
    for(int i = 0 ; i < number ; i ++ )
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    free(a) ;
    return 0 ;
}