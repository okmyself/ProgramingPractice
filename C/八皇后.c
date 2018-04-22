#include <stdio.h>
#define N 8
outPut(int map[N][N]);
setZero(int map[N][N]);
setQueen(int map[N][N], int m, int n);

int map[N][N] = { 0 };		//0:空白；1:皇后；-1:不可放置皇后的空白
int temp[N][N][N] = { 0 };

int main(void)
{
	setQueen(map, 3, 4);
	outPut(map);
	return 0;
}

outPut(int map[N][N])
{
	int i, j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			printf("%d\t", map[i][j]);
		putchar('\n');
	}
}

setZero(int map[N][N])
{
	int i, j;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			map[i][j] = 0;
}

setQueen(int map[N][N], int m, int n)
{
	int i, j;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
		{
			if(i == m && j == n)
				map[i][j] = 1;
			else if(i == m)
				map[i][j] = -1;
			else if(j == n)
				map[i][j] = -1;
			else if(i - m == j - m)
				map[i][j] = -1;
			else
				map[i][j] = 0;
		}
}
