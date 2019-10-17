#include <stdio.h>
#include <stdlib.h>

int SqListMethod(int m, int n);
int LinkListMethod(int m, int n);

int main()
{
    int m, n;
    printf("请输入猴子的个数m=");
    scanf("%d", &m);
    printf("请输入数到数字的最大值n=");
    scanf("%d", &n);
    int king = SqListMethod(m, n);
    printf("向量结构求解最后一只猴子的编号为%d\n", king);
    king = LinkListMethod(m, n);
    printf("链表结构求解最后一只猴子的编号为%d\n", king);
    return 0;
}

int SqListMethod(int m, int n)
{
    int *monkey = (int*)malloc(m * sizeof(int));
    int i;
    for(i = 0; i < m; i++)
        monkey[i] = i + 1;  //给猴子分配编号
    int numOfMonkey = m;    //圈中猴子的数量
    int j = 1;              //圈中猴子数到的数字
    int position = 0;       //正在数的猴子的位置
    while(numOfMonkey > 1)
    {
        if(j < n)
        {
            position++;
            j++;
        }
        else
        {
            //删除这个猴子，后面的猴子前移
            for(i = position; i < numOfMonkey; i++)
                monkey[i] = monkey[i + 1];
            numOfMonkey--;
            j = 1;
        }
        if(position >= numOfMonkey) position = 0;   //注意position从0开始
    }
    int result = *monkey;
    free(monkey);
    return result;
}

typedef struct monkey {
    int No;   //编号
    struct monkey *next;
} Monkey;
typedef Monkey* Circle;

int LinkListMethod(int m, int n)
{
    Circle temp, cur, pre;
    temp = cur = pre = (Circle)malloc(sizeof(Monkey));
    int i;
    //建立猴子链表
    for(i = 1; i < m; i++)
    {
        pre->No = i;
        cur = (Circle)malloc(sizeof(Monkey));
        pre->next = cur;
        pre = cur;
    }
    cur->No = m;
    cur->next = temp;
    //报数
    i = 1;  //当前正在报的数字
    while(cur->next != cur)
    {
        if(i < n)
        {
            cur = cur->next;
            i++;
        }
        else
        {
            //删除报到n的猴子
            temp = cur->next;
            cur->next = temp->next;
            i = 1;
            free(temp);
        }
    }
    int result = cur->No;
    free(cur);
    return result;
}


