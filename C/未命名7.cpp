#include <stdio.h>

int main(void)
{
	int i, t, N, j, k, a;
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
	return 0;
}
