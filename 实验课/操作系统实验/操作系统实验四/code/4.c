/*  usage of kill,signal,wait  */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>

int flag;
void stop();
int main(void)
{
    int pid1, pid2;
    signal(3, stop);    //设置信号3的处理函数为stop
    while ((pid1 = fork()) == -1) ; //创建一个子进程
    if (pid1 > 0)   //当前进程为父进程
    {
        while ((pid2 = fork()) == -1) ; //创建另一个子进程
        if (pid2 > 0)   //当前进程为父进程
        {
            flag = 1;
            sleep(5);
            kill(pid1, 16); //向子进程1发送信号16
            kill(pid2, 17); //向子进程2发送信号17
            wait(0);    //暂停当前进程，直到信号来到或子进程结束
            wait(0);
            printf("\n parent is killed\n");
            exit(EXIT_SUCCESS);
        }
        else    //当前进程为子进程2
        {
            flag = 1;
            signal(17, stop);   //设置信号17的处理函数为stop
            printf("\n child2 is killed by parent\n");
            exit(EXIT_SUCCESS);
        }
    }
    else    //当前进程为子进程1
    {
        flag = 1;
        signal(16, stop);
        printf("\n child1 is killed by parent\n");
        exit(EXIT_SUCCESS);
    }
}

void stop()
{
    flag = 0;
}