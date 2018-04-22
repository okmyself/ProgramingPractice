#include <stdio.h>

int main(void)
{
	int i, t, N, j, k, a;
	int one = -1, two = -1, three = -1;
	scanf("%d", &N);
	char name[N][9]; 
	int average[N];
	int times[N];
	for(i = 0; i < N; i++)
	{
		scanf("%s", name[i]);
		scanf("%d", &t);
		int label[t];
		average[i] = 0;
		times[i] = 0;
		for(j = 0; j < t; j++)
		{
			scanf("%d", &label[j]);
			a = 0;
			for(k = 0; k < j; k++)
			{
				if(label[j] == label[k])
					a = 1;
			}
			if(a != 1)
				times[i]++;
		}
	}
	for(i = 0; i < N; i++)
	{
		if(one = -1)
			one = i;
		else if(times[i] > times[one])
			one = i;
	}
	for(i = 0; i < N; i++)
	{
		if(two = -1)
			if(times[i] < times[one])
				two = i;
		else if(times[i] > times[two] && i != one)
			two = i;
	}
	for(i = 0; i < N; i++)
	{
		if(three = -1)
		{
			if(times[i] < times[two])
				three = i;
		}
		else if(times[i] > times[three] && i != one && i != two)
			three = i;
	}
	printf("%s %s %s", one=-1?"-":name[one], two=-1?"-":name[two], three=-1?"-":name[three]);
	return 0;
}
