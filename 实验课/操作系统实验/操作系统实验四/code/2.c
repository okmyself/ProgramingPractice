/*	process using time  */
#include<stdio.h>
#include<stdlib.h>
#include<sys/times.h>
#include<time.h>
#include<unistd.h>

void time_print(char *,clock_t);
void calc();

int main(void) {
    clock_t start,end;
    struct tms t_start,t_end;
    start = times(&t_start);    //计算起始时间
    
    calc();
    // system("grep the /usr/doc/*/* > /dev/null 2> /dev/null");
    /* command > /dev/null是将标准输出重定向到空设备中（丢弃）
       command 2> /dev/null是将标准错误重定向到空设备中（丢弃） */
    end=times(&t_end);  //计算结束时间

    time_print("elapsed",end-start);
    puts("parent times");
    time_print("\tuser CPU",t_end.tms_utime);
    time_print("\tsys CPU",t_end.tms_stime);

    puts("child times");
    time_print("\tuser CPU",t_end.tms_cutime);
    time_print("\tsys CPU",t_end.tms_cstime);

    exit(EXIT_SUCCESS);
}

void time_print(char *str,clock_t time) {   //输出时间
    long tps = sysconf(_SC_CLK_TCK);    //获得CPU内部时钟每秒中断个数
    printf("%s: %6.2f secs\n",str,(float)time/tps);
}

void calc() //计算密集型程序，计算0-300000之间的素数并输出
{
    int i = 0, j = 0, sum = 0;
    for(i = 0; i < 300000; i++)
    {
        for(j = 2; j < i; j++)
        {
            if(i % j == 0) break;
        }
        if(j == i)
        {
            printf("%d ", i);
            sum++;
            if(sum % 10 == 0) putchar('\n');
        }
    }
    putchar('\n');
}