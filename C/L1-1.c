#include <stdio.h>

int main(void)
{
	int i = 0, num;
	do
	{
		scanf("%d", &num);
		i++;
	} while(num != 250);
	printf("%d", i);
	return 0;
}
