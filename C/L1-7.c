#include <stdio.h>

int main(void)
{
	int i, n, a, b;
	char s[4];
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%s %d %d", s, &a, &b);
		if(15 <= a && a <= 20 && 50 <= b && b <= 70)
		{}
		else printf("%s\n", s);
	} 
	return 0;
}
