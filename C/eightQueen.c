#include <stdio.h>
#define N 8

int total = 0;
int c[N];

queen(int row)
{
	int col;
	if(row == N)
		total++;
	else
		for(col = 0; col < row; col++)
		{
			c[row] = col;
			if(is_ok(row))
				queen(row + 1);
		}
}

int is_ok(int row)
{
	int j;
	for(j = 0; j < row; j++)
		if(c[row] == c[j] || row - c[row] == j - c[j] || row + c[row] == j + c[j])
			return 0;
	return 1;
}

int main(void)
{
	queen(0);
	printf("%d", total);
}
