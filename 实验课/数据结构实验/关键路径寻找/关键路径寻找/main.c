#include <stdio.h>
#include <stdlib.h>

#define ALLOC_MEM_ERROR -1
#define CIRCLE_EXIST 1
#define OK 0

typedef int Status;

typedef struct vexnode
{
    int vex;                        //记录后继结点
    int dut;                        //权值
    struct vexnode *next;
} *Vexnode;

typedef struct
{
    int index;                      //记录入度indegree、链栈的结点
    
    char data[5];                   //记录结点的数据（名字）
    Vexnode out;
} CPMAdj;

CPMAdj* Create(int n);
void Destroy(CPMAdj *A, int n);
Status CPM(CPMAdj *A, int n);

int main(void)
{
    int n;
    printf("请输入结点的个数：");
    scanf("%d", &n);
    CPMAdj *A = Create(n);
    CPM(A, n);
    Destroy(A, n);
    return 0;
}

CPMAdj* Create(int n)
{
    int u, k, dut;
    CPMAdj *A;
    Vexnode p;
    
    A = (CPMAdj*)calloc(n, sizeof(CPMAdj));
    if(A == NULL) exit(ALLOC_MEM_ERROR);
    printf("请输入结点的名称（不超过5个字符）：\n");
    for(k = 0; k < n; k++)
    {
        printf("%d: ", k);
        scanf("%s", A[k].data);
        A[k].index = 0;             //初始化入度
        A[k].out = NULL;
    }
    
    printf("请输入各个活动(0<=u,k<n,输入不在此范围内则停止)：\n");
    printf("u k dut\n");
    scanf("%d%d%d", &u, &k, &dut);
    while(u >= 0 && u < n && k >= 0 && k < n)
    {
        //把结点插在开头，写入权值、入度
        p = (Vexnode)malloc(sizeof(struct vexnode));
        p->vex = k;
        A[k].index++;               //入度增加
        p->dut = dut;
        p->next = A[u].out;
        A[u].out = p;
        scanf("%d%d%d", &u, &k, &dut);
    }
    return A;
}

void Destroy(CPMAdj *A, int n)
{
    Vexnode p, temp;
    int i;
    for(i = 0; i < n; i++)
    {
        p = A[i].out;
        while(p)
        {
            temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(A);
}

Status CPM(CPMAdj *A, int n)
{
    //拓扑排序计算Ve
    int Ve[n], Vl[n];               //事件最早、晚发生时间
    int ftop = -1, btop = -1;       //拓扑栈、逆拓扑栈栈顶指针，-1表示栈中没有元素
    int m = 0;                      //输出顶点个数
    int u, k;                       // <u,k>表示一条边
    int i;
    int endnode;                    //拓扑排序终点元素
    Vexnode p;
    for(i = 0; i < n; i++)
    {
        if(A[i].index == 0)         //寻找入度为0的结点
        {
            A[i].index = ftop;
            ftop = i;               //入栈
        }
        Ve[i] = 0;                   //最早发生时间初始化为0
    }
    //计算Ve
    while(ftop != -1)               //拓扑栈中存在入度为0的结点
    {
        u = ftop;
        ftop = A[ftop].index;       //入度为0的结点退出拓扑栈
        
        A[u].index = btop;
        btop = u;                   //压入逆拓扑栈
        
//        output[m] = A[u].data;      //保存拓扑排序结果到数组
        
        m = m + 1;
        p = A[u].out;
        
        while(p)                    //删除所有出边<u,k>
        {
            k = p->vex;
            A[k].index = A[k].index - 1;
            if(A[k].index == 0)     //入度若减1后为0则将它入栈
            {
                A[k].index = ftop;
                ftop = k;
            }
            //对于所有出边<u,k>，Ve[k]中存储事件u最早发生时间与最大权值之和
            if(Ve[k] < Ve[u] + p->dut)
                Ve[k] = Ve[u] + p->dut;
            
            p = p->next;
        }
    }
    if(m < n) return CIRCLE_EXIST;  //有环图
    //计算Vl
    endnode = btop;                 //保存终点元素
    Vl[endnode] = Ve[endnode];
    
    while(btop != -1)               //逆拓扑栈中存在元素，依次求Vl
    {
        u = btop;
        btop = A[btop].index;       //逆拓扑栈退栈
        
        Vl[u] = Ve[endnode];        //全部初始化为时间的最大值
        p = A[u].out;
        while(p)
        {
            k = p->vex;
            if(Vl[u] > Vl[k] - p->dut)
                Vl[u] = Vl[k] - p->dut;
            p = p->next;
        }
    }
    //输出关键路径
    printf("ACT\t\tE\tL\n");        //活动、最早发生时间、最晚发生时间
    for(k = 0; k < n; k++)
    {
        p = A[k].out;
        while(p)
        {
            if(Ve[k] == Vl[p->vex] - p->dut)
                printf("*");
            
            printf("<%s,%s>\t%d\t%d\n", A[k].data, A[p->vex].data,
                   Ve[k], Vl[p->vex] - p->dut);
            
            p = p->next;
        }
    }
    return OK;
}
