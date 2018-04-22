#include <stdio.h>

void move(int n, char* from, char* to, char* other);

int main(void)
{
	int n;
	printf("Input how many dishes do you want to move:\n");
	scanf("%d", &n);
	move(n, "A", "C", "B");
	return 0;
}

void move(int n, char* from, char* to, char* other)
{
	static int i = 1;
	if(n == 1)
		printf("第%d次移动：从%s移动%d到%s\n", i++, from, i, to);
	else
	{
		move(n - 1, from, other, to);
		move(1, from, to, other);
		move(n - 1, other, to, from);
	}
}
