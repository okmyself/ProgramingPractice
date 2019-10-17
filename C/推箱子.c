#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define ROW 8
#define RANGE 6
int count_1();
int count_2();

int up();
int down();
int left();
int right();
int outPut();
int find();

int G_point_x, G_point_y;
int G_map[ROW][RANGE] = { 0 };

int main(void)
{
	/*定义的游戏界面模型*/
	int map[ROW][RANGE] = {
		{ 0, 1, 1, 1, 1, 0 },
		{ 1, 1, 0, 0, 1, 0 },
		{ 1, 3, 2, 0, 1, 0 },
		{ 1, 1, 2, 0, 1, 1 },
		{ 1, 1, 0, 2, 0, 1 },
		{ 1, 4, 2, 0, 0, 1 },
		{ 1, 4, 4, 5, 4, 1 },
		{ 1, 1, 1, 1, 1, 1 }
	};  /*0是空白 1是墙 2是箱子 3是人 4是目标 5是目标上的箱子*/
	system("title 推箱子2.0");
	memcpy(G_map, map, sizeof(map));
	printf("***按任意键开始游戏***\n");
	_getch();

	for (; ; )
	{
		system("cls");
		outPut();
		find();
		switch (getch())
		{
		case 'w':
		case 72:
		{
			up();
			break;
		}
		case 's':
		case 80:
		{
			down();
			break;
		}
		case 'a':
		case 75:
		{
			left();
			break;
		}
		case 'd':
		case 77:
		{
			right();
			break;
		}
		case 'r':/*重新开始游戏*/
		{
			memcpy(G_map, map, sizeof(map));
			break;
		}
		}
		if (count_1() == count_2())
		{
			system("cls");
			outPut();
			printf("\n游戏胜利，按任意键退出\n");
			system("pause");
			return 0;
		}
	}
	system("cls");
	outPut();
	system("pause");
	return 0;
}
/*”屏幕上输出下列图形：“■”代表墙、“⊙”代表人、“□”代表箱子、“☆”代表目标点、
“　”代表空白区域或人可走的区域、“★”表示已经在目标点上的箱子、“●”表示在目标点上的人*/
int outPut(void)
{
	for (G_point_x = 0; G_point_x < ROW; G_point_x++)
	{
		for (G_point_y = 0; G_point_y < RANGE; G_point_y++)
		{
			if (G_map[G_point_x][G_point_y] == 0)
				printf("　"); /*输出空白*/
			if (G_map[G_point_x][G_point_y] == 1)
				printf("■"); /*输出墙*/
			if (G_map[G_point_x][G_point_y] == 2)
				printf("□"); /*输出箱子*/
			if (G_map[G_point_x][G_point_y] == 3)
				printf("⊙"); /*输出人的位置*/
			if (G_map[G_point_x][G_point_y] == 4)
				printf("☆"); /*输出目标点*/
			if (G_map[G_point_x][G_point_y] == 5)
				printf("★"); /*输出箱子在目标点上*/
			if (G_map[G_point_x][G_point_y] == 6)
				printf("●"); /*输出人在目标点上*/
		}
		printf("\n");
	}
	return 0;
}
/*数出目标点的个数（包含箱子或人在目标点上）*/
int count_1(void)
{
	int i = 0;
	for (G_point_x = 0; G_point_x < ROW; G_point_x++)
		for (G_point_y = 0; G_point_y < RANGE; G_point_y++)
		{
			if (G_map[G_point_x][G_point_y] == 4 ||
				G_map[G_point_x][G_point_y] == 5 ||
				G_map[G_point_x][G_point_y] == 6)
				i++;
		}
	return i;
}
/*数出在目标点上的箱子的个数*/
int count_2(void)
{
	int i = 0;
	for (G_point_x = 0; G_point_x < ROW; G_point_x++)
		for (G_point_y = 0; G_point_y < RANGE; G_point_y++)
		{
			if (G_map[G_point_x][G_point_y] == 5)
				i++;
		}
	return i;
}
/*找到自己的位置*/
int find(void)
{
	for (G_point_x = 0; G_point_x < ROW; G_point_x++)
		for (G_point_y = 0; G_point_y < RANGE; G_point_y++)
		{
			if (G_map[G_point_x][G_point_y] == 3 || G_map[G_point_x][G_point_y] == 6)
				return 0;
		}
	return 0;
}
/*按w的时候的输出结果*/
int up(void)
{
	if (G_map[G_point_x][G_point_y] == 3 ||
		G_map[G_point_x][G_point_y] == 6) /*确定是自己的位置*/
	{
		switch (G_map[G_point_x - 1][G_point_y])
		{
		case 0: /*上面一个格子是空的*/
		{
			G_map[G_point_x - 1][G_point_y] = 3;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 4: /*上面一个格子是目标点*/
		{
			G_map[G_point_x - 1][G_point_y] = 6;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 2: /*上面一个格子是箱子*/
		{
			if (G_map[G_point_x - 2][G_point_y] == 0)
			{
				G_map[G_point_x - 2][G_point_y] = 2;
				G_map[G_point_x - 1][G_point_y] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x - 2][G_point_y] == 4)
			{
				G_map[G_point_x - 2][G_point_y] = 5;
				G_map[G_point_x - 1][G_point_y] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		case 5: /*上面一个格子是目标点上的箱子*/
		{
			if (G_map[G_point_x - 2][G_point_y] == 0)
			{
				G_map[G_point_x - 2][G_point_y] = 2;
				G_map[G_point_x - 1][G_point_y] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x - 2][G_point_y] == 4)
			{
				G_map[G_point_x - 2][G_point_y] = 5;
				G_map[G_point_x - 1][G_point_y] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		}
	}
	return 0;
}
/*按s的时候的输出结果*/
int down(void)
{
	if (G_map[G_point_x][G_point_y] == 3 ||
		G_map[G_point_x][G_point_y] == 6) /*确定是自己的位置*/
	{
		switch (G_map[G_point_x + 1][G_point_y])
		{
		case 0: /*下面一个格子是空的*/
		{
			G_map[G_point_x + 1][G_point_y] = 3;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 4: /*下面一个格子是目标点*/
		{
			G_map[G_point_x + 1][G_point_y] = 6;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 2: /*下面一个格子是箱子*/
		{
			if (G_map[G_point_x + 2][G_point_y] == 0)
			{
				G_map[G_point_x + 2][G_point_y] = 2;
				G_map[G_point_x + 1][G_point_y] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x + 2][G_point_y] == 4)
			{
				G_map[G_point_x + 2][G_point_y] = 5;
				G_map[G_point_x + 1][G_point_y] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		case 5: /*下面一个格子是目标点上的箱子*/
		{
			if (G_map[G_point_x + 2][G_point_y] == 0)
			{
				G_map[G_point_x + 2][G_point_y] = 2;
				G_map[G_point_x + 1][G_point_y] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x + 2][G_point_y] == 4)
			{
				G_map[G_point_x + 2][G_point_y] = 5;
				G_map[G_point_x + 1][G_point_y] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		}
	}
	return 0;
}
/*按a的时候的输出结果*/
int left(void)
{
	if (G_map[G_point_x][G_point_y] == 3 ||
		G_map[G_point_x][G_point_y] == 6) /*确定是自己的位置*/
	{
		switch (G_map[G_point_x][G_point_y - 1])
		{
		case 0: /*左面一个格子是空的*/
		{
			G_map[G_point_x][G_point_y - 1] = 3;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 4: /*左面一个格子是目标点*/
		{
			G_map[G_point_x][G_point_y - 1] = 6;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 2: /*左面一个格子是箱子*/
		{
			if (G_map[G_point_x][G_point_y - 2] == 0)
			{
				G_map[G_point_x][G_point_y - 2] = 2;
				G_map[G_point_x][G_point_y - 1] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x][G_point_y - 2] == 4)
			{
				G_map[G_point_x][G_point_y - 2] = 5;
				G_map[G_point_x][G_point_y - 1] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		case 5: /*左面一个格子是目标点上的箱子*/
		{
			if (G_map[G_point_x][G_point_y - 2] == 0)
			{
				G_map[G_point_x][G_point_y - 2] = 2;
				G_map[G_point_x][G_point_y - 1] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x][G_point_y - 2] == 4)
			{
				G_map[G_point_x][G_point_y - 2] = 5;
				G_map[G_point_x][G_point_y - 1] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		}
	}
	return 0;
}
/*按d的时候的输出结果*/
int right(void)
{
	if (G_map[G_point_x][G_point_y] == 3 ||
		G_map[G_point_x][G_point_y] == 6) /*确定是自己的位置*/
	{
		switch (G_map[G_point_x][G_point_y + 1])
		{
		case 0: /*右面一个格子是空的*/
		{
			G_map[G_point_x][G_point_y + 1] = 3;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 4: /*右面一个格子是目标点*/
		{
			G_map[G_point_x][G_point_y + 1] = 6;
			if (G_map[G_point_x][G_point_y] == 3)
				G_map[G_point_x][G_point_y] = 0;
			else
				G_map[G_point_x][G_point_y] = 4;
			break;
		}
		case 2: /*右面一个格子是箱子*/
		{
			if (G_map[G_point_x][G_point_y + 2] == 0)
			{
				G_map[G_point_x][G_point_y + 2] = 2;
				G_map[G_point_x][G_point_y + 1] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x][G_point_y + 2] == 4)
			{
				G_map[G_point_x][G_point_y + 2] = 5;
				G_map[G_point_x][G_point_y + 1] = 3;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		case 5: /*右面一个格子是目标点上的箱子*/
		{
			if (G_map[G_point_x][G_point_y + 2] == 0)
			{
				G_map[G_point_x][G_point_y + 2] = 2;
				G_map[G_point_x][G_point_y + 1] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			else if (G_map[G_point_x][G_point_y + 2] == 4)
			{
				G_map[G_point_x][G_point_y + 2] = 5;
				G_map[G_point_x][G_point_y + 1] = 6;
				if (G_map[G_point_x][G_point_y] == 3)
					G_map[G_point_x][G_point_y] = 0;
				else
					G_map[G_point_x][G_point_y] = 4;
			}
			break;
		}
		}
	}
	return 0;
}
