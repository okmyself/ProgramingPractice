#include <stdio.h>
#define N 81

char toUpper(char c);

int main(void)
{
	int i, j, k, times;
	char str1[N], str2[N];
	char result[N];
	scanf("%s", str1);
	scanf("%s", str2);
	for(i = 0, j = 0, k = 0; j < N; i++, j++)
	{
		if(str2[j] == '\0')
			break;
		while(toUpper(str1[i]) != toUpper(str2[j]))
			result[k++] = toUpper(str1[i++]);
	}
	while(str1[i] != '\0')
		result[k++] = str1[i++];
	for(i = 0; i < k; i++)
	{
		times = 0;
		for(j = 0; j < i; j++)
		{
			if(result[i] == result[j])
				times++;
		}
		if(times == 0)
			putchar(result[i]);
	}
}

char toUpper(char c)
{
	if(c >= 'A' && c <= 'Z')
		return c;
	else if(c >= 'a' && c <= 'z')
		return c - 'a' + 'A';
	else
		return c;
}
