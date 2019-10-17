#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define FULL 2
#define ERROR 3
#define LEVEL_NOT_EXSIT 4
#define ROOM_NOT_EXSIT 5
#define BED_NOT_EXSIT 6

typedef int Status;

struct Bed {
    int number;         //床号
    char name[20];      //名字最多10个汉字
    int age;            //年龄
    time_t time;        //到达日期
    struct Bed *next;
};

struct Room {
    int number;         //房间号
    int persons;        //房间已住人数
    int sex;            //该房间住的人的性别，1表示男，0表示女
    struct Bed *bed;    //指向Bed链表
    struct Room *next;
};

struct Level {
    int n;              //该等级房间的个数
    int rooms;          //该等级已住人房间的个数
    int persons;        //该等级已住人数
    int beds;           //房间的床数
    struct Room *room;  //指向Room链表
};

struct Level* Init(int N);
Status Checkin(int N, struct Level *levels);
Status Checkout(int N, struct Level *levels);
void Enquire(int N, struct Level *levels);
void Destroy(int N, struct Level *levels);

int main(void)
{
    int input, N;
    printf("请输入客店的等级数量N=");
    scanf("%d", &N);
    if(N < 1)
    {
        printf("Error!");
        exit(ERROR);
    }
    struct Level *levels = Init(N);
    printf("请选择您需要的服务：\n\t1.入住旅店\n\t2.离店退房\n\t3.查询入住情况\n\t其它.退出\n:");
    scanf("%d", &input);
    while(input == 1 || input == 2 || input == 3)
    {
        switch (input) {
            case 1:
                if(Checkin(N, levels) == FULL) printf("满客\n");
                break;
            case 2:
                if(Checkout(N, levels) != OK) printf("输入有误\n");
                break;
            case 3:
                Enquire(N, levels);
                break;
        }
        printf("请选择您需要的服务：\n\t1.入住旅店\n\t2.离店退房\n\t3.查询入住情况\n\t其它数字.退出\n:");
        scanf("%d", &input);
    }
    Destroy(N, levels);
    return 0;
}

struct Level* Init(int N)   //N是等级数量
{
    struct Level *pLevel = (struct Level*)malloc(sizeof(struct Level) * N);  //动态创建长度为N的数组
    int k;
    printf("请输入第k级客房个数A(k):\n");
    for(k = 1; k <= N; k++) //输出1-N(提示信息)
        printf("%d ", k);
    putchar('\n');
    for(k = 0; k < N; k++)  //输入A(k)
        scanf("%d", &pLevel[k].n);
    printf("请输入第k级客房单人床个数B(k):\n"); //床的数量只和等级有关
    for(k = 1; k <= N; k++)
        printf("%d ", k);
    putchar('\n');
    for(k = 0; k < N; k++)
    {
        scanf("%d", &pLevel[k].beds);
        pLevel[k].room = NULL;
        pLevel[k].rooms = 0;    //住了房间的个数
        pLevel[k].persons = 0;  //住了的人数
    }
    return pLevel;
}

Status Checkin(int N, struct Level *levels)
{
    int level, sex;
    char ch;
    do
    {
        printf("请输入您要入住的等级(1-%d):", N);
        scanf("%d", &level);
        if(level < 1 || level > N)
        {
            printf("Error!");
            exit(ERROR);
        }
        level--;    //数组下标从0开始
        if(levels[level].persons >= levels[level].n * levels[level].beds)   //该等级客满
        {
            printf("满客，是否更改等级？(y/n)\n:");
//            scanf("%c", &ch); //也会读到换行符
            while((ch = getchar()) == '\n') ;   //直到读到一个非换行符停止
            if(ch == 'Y' || ch == 'y') continue;    //重新进行此循环
            else return FULL;   //返回客满
        }
        else        //仍有空位，但未判断男女
        {
            struct Room *pRoom = levels[level].room;
            printf("请输入您的性别(1代表男，其它数字代表女)：");
            scanf("%d", &sex);
            if(sex != 1) sex = 0;   //用0代表女
            int flag = 0;   //是否存在没住满房间的标记，存在为0
            while(pRoom)
            {
                //该性别存在没住满的房间
                if(pRoom->sex == sex && pRoom->persons < levels[level].beds)
                {
                    struct Bed *pBed = (struct Bed*)malloc(sizeof(struct Bed)); //分配一个Bed结点
                    printf("请输入您的姓名：");
                    scanf("%s", pBed->name);
                    printf("请输入您的年龄：");
                    scanf("%d", &pBed->age);
                    time(&pBed->time);  //保存系统时间
                    //计算该给这个人的床号
                    struct Bed *curBed = NULL, *preBed = pRoom->bed; //preBed指向第一个床
                    if(preBed && preBed->number == 1)
                    //情况①：第一个床住着人
                    {
                        curBed = preBed->next;  //curBed是第二个床
                        while(curBed)
                        {
                            //preBed和curBed之间有没住的床
                            if(curBed->number - preBed->number > 1) break;
                            //两个指针向后移
                            preBed = preBed->next;
                            curBed = curBed->next;
                        }
                    }
                    else if(preBed)
                    //情况②：第一个床没人并且后面的床部分有人
                    {
                        curBed = preBed;
                        preBed = NULL;
                    }
                    else preBed = NULL;
                    //将pBed插在curBed和preBed之间
                    pBed->next = curBed;
                    if(preBed)
                    {
                        //满足情况①②
                        preBed->next = pBed;    //前一个指向插入的结点
                        pBed->number = preBed->number + 1;  //插入的结点的编号是前一个编号+1
                    }
                    else
                    {
                        //没有床有人，插入的床是唯一的床
                        pRoom->bed = pBed;  //让房间的bed指针直接指向插入的结点
                        pBed->number = 1;   //编号为1
                    }
                    pRoom->persons++;       //房间记录的人数+1
                    levels[level].persons++;    //等级记录的人数+1
                    flag = 1;   //存在没住满的房间，并且已经住进去了
                    break;
                }
                pRoom = pRoom->next;    //工作指针向后移动
            }
            //该性别有人的房间住满了，没住进去，建立空房
            if(flag == 0)
            {
                struct Room *preRoom = levels[level].room, *curRoom = NULL;
                if(preRoom && preRoom->number == 1)
                //情况①：第一个房间住着人
                {
                    curRoom = preRoom->next;
                    while(curRoom)
                    {
                        if(curRoom->number - preRoom->number > 1) break;    //找到第一个没建立的房间
                        //向后移动
                        preRoom = preRoom->next;
                        curRoom = curRoom->next;
                    }
                }
                else if(preRoom)
                //情况②：第一个房间没人并且后面的房间部分有人
                {
                    curRoom = preRoom;
                    preRoom = NULL;
                }
                else preRoom = NULL;
                
                if(preRoom && preRoom->number >= levels[level].n)   //房间满了
                {
                    printf("满客，是否更改等级？(y/n)\n:");
                    while((ch = getchar()) == '\n');
//                    scanf("%c", &ch);
                    if(ch == 'Y' || ch == 'y') continue;
                    else return FULL;
                }
                //建立空房
                struct Room *pRoom = (struct Room*)malloc(sizeof(struct Room));
                pRoom->next = curRoom;
                if(preRoom)
                {
                    preRoom->next = pRoom;
                    pRoom->number = preRoom->number + 1;
                }
                else
                {
                    levels[level].room = pRoom;
                    pRoom->number = 1;
                }
                //在空房里添加床
                struct Bed *pBed = (struct Bed*)malloc(sizeof(struct Bed));
                printf("请输入您的姓名：");
                scanf("%s", pBed->name);
                printf("请输入您的年龄：");
                scanf("%d", &pBed->age);
                time(&pBed->time);
                pBed->number = 1;
                pBed->next = NULL;      //这句很重要
                pRoom->bed = pBed;
                pRoom->persons = 1;     //住了一个人
                pRoom->sex = sex;
                
                levels[level].rooms++;
                levels[level].persons++;
            }
        }
        break;
    } while(1);
    return OK;
}

Status Checkout(int N, struct Level *levels)
{
    int level, roomNumber, bedNumber;
    printf("请输入您的等级：");
    scanf("%d", &level);    //输入等级存在level中
    if(level > N || level < 1) return LEVEL_NOT_EXSIT;
    level--;
    printf("请输入您的房间号：");
    scanf("%d", &roomNumber);
    struct Room *curRoom = levels[level].room, *preRoom = NULL; //curRoom是等级level的第一个房间
    if(curRoom && curRoom->number != roomNumber)
    //第一个房间不是要退房的
    {
        preRoom = curRoom;
        curRoom = curRoom->next;
    }
    while(curRoom && curRoom->number != roomNumber)
        curRoom = curRoom->next;
    if(curRoom == NULL) return ROOM_NOT_EXSIT;
        
    printf("请输入您的床号：");
    scanf("%d", &bedNumber);
    struct Bed *curBed = curRoom->bed, *preBed = NULL;
    if(curBed && curBed->number != bedNumber)
    //第一个床不是要退的
    {
        preBed = curBed;
        curBed = curBed->next;
    }
    while(curBed && curBed->number != bedNumber)
        curBed = curBed->next;
    if(curBed == NULL) return BED_NOT_EXSIT;
    
    //删除床位
    levels[level].persons--;
    curRoom->persons--;
    if(preBed == NULL)     //该Bed为头结点
    {
        curRoom->bed = curBed->next;
        if(curRoom->persons == 0)   //删掉这个房间
        {
            levels[level].rooms--;
            if(preRoom == NULL)    //该Room为头结点
                levels[level].room = curRoom->next;
            else            //该Room不为头结点，房间不会全为空
                preRoom->next = curRoom->next;
            free(curRoom);
        }
    }
    else            //该Bed不为头结点，房间不会为空
        preBed->next = curBed->next;
    free(curBed);   //释放的是curBed
    return OK;
}

void Enquire(int N, struct Level *levels)
{
    int i, j;
    char *time;
    printf("入住信息：\n姓名\t\t年龄\t性别\t客房等级\t房间号\t床位号\t到达日期\n================================================================\n");
    for(i = 0; i < N; i++)
    {
        struct Room *pRoom = levels[i].room;
        while(pRoom)
        {
            struct Bed *pBed = pRoom->bed;
            for(j = 0; j < pRoom->persons; j++)
            {
                time = ctime(&pBed->time);
                if(pRoom->sex == 1)
                    printf("%s\t\t%d\t男\t%d\t\t%d\t\t%d\t\t%s", pBed->name, pBed->age, i + 1, pRoom->number, pBed->number, time);
                else
                    printf("%s\t\t%d\t女\t%d\t\t%d\t\t%d\t\t%s", pBed->name, pBed->age, i + 1, pRoom->number, pBed->number, time);
                pBed = pBed->next;
            }
            pRoom = pRoom->next;
        }
    }
}

void Destroy(int N, struct Level *levels)
{
    int i;
    for(i = 0; i < N; i++)
    {
        struct Room *pRoom = levels[i].room, *tempRoom;
        while(pRoom)
        {
            struct Bed *pBed = pRoom->bed, *tempBed;
            while(pBed)
            {
                tempBed = pBed;
                pBed = pBed->next;
                free(tempBed);
            }
            tempRoom = pRoom;
            pRoom = pRoom->next;
            free(tempRoom);
        }
    }
    free(levels);
}
