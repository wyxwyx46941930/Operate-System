#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//给定矩阵的边长
int Number_one, Number_two, Number_three;
//申请全局矩阵
int A[100][100];
int B[100][100];
int C[100][100];
//构造结构体完成边长设定
struct v
{
    int i, j;
};
//计算矩阵的乘积
void *calculate(void *data) {
    struct v *a = (struct v*)data;
    int i = a->i;
    int j = a->j;
    for (int k = 0; k < Number_two; k++) {
        C[i][j] += A[i][k] * B[k][j];
    }
    pthread_exit(NULL);
}

int main() {
    printf("Number_one:");
    scanf("%d",&Number_one) ;
    printf("Number_one:");
    scanf("%d", &Number_two) ;
    printf("Number_one:");
    scanf("%d", &Number_three) ;

    //输入A矩阵
    printf("The first Matrix, size(Number_one * Number_two)\n");
    for (int i = 0; i < Number_one; i++) {
        for (int j = 0; j < Number_two; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    //输入B矩阵
    printf("The second Matrix, size(Number_two * Number_three)\n");
    for (int i = 0; i < Number_two; i++) {
        for (int j = 0; j < Number_three; j++) {
            scanf("%d",&B[i][j]);
        }
    }
    //初始化C矩阵
    for (int i = 0; i < Number_one; i++) {
        for (int j = 0; j < Number_three; j++) {
            C[i][j] = 0;
        }
    }
    //创建M*N个线程指针
    pthread_t tid[Number_one * Number_three];
    //设定线程属性
    pthread_attr_t attr;
    // 初始化线程属性为默认值
    pthread_attr_init(&attr);
    //为M*N个线程指针分配M*N个线程
    for (int i = 0; i < Number_one; i++) {
        for (int j = 0; j < Number_three; j++) {
            struct v *a = (struct v*)malloc(sizeof(struct v));
            a -> i = i;
            a -> j = j;
            pthread_create(&tid[i * Number_three + j], &attr, calculate, (void*)a);
        }
    }
    //调用阻塞线程函数
    for (int i = 0; i < Number_one * Number_three; i++) {
        pthread_join(tid[i], NULL);
    }
    //完成输出
    printf("C matrix is:\n");
    for (int i = 0; i < Number_one; i++) {
        for (int j = 0; j < Number_three; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}