#include <stdio.h>

int main(void)
{
	int K, i = 1;
	char get[8];
	scanf("%d", &K);
	do
	{
		scanf("%s", get);
		if(i % (K + 1) == 0)
			printf("%s\n", get);
		else if(get[0] == 'E')
			break;
		else if(get[0] == 'C')
			printf("Bu\n");
		else if(get[0] == 'J')
			printf("ChuiZi\n");
		else if(get[0] == 'B')
			printf("JianDao\n");
		i++;
	} while(1);
	return 0;
}
