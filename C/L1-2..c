#include <stdio.h>

int main(void)
{
	int mm, dd, yyyy;
	scanf("%d-%d-%d", &mm, &dd, &yyyy);
	printf("%d-", yyyy);
	if(mm < 10)
		printf("0%d-", mm);
	else
		printf("%d-", mm);
	if(dd < 10)
		printf("0%d", dd);
	else
		printf("%d", dd);
	return 0;
}
