#include <stdio.h>

int main(void)
{
	int i, j, k, Ra, Ca, Rb, Cb;
	//ÊäÈë¾ØÕóA
	scanf("%d %d", &Ra, &Ca);
	int matrixA[Ra][Ca];
	for(i = 0; i < Ra; i++)
		for(j = 0; j < Ca; j++)
			scanf("%d", &matrixA[i][j]);
	//ÊäÈë¾ØÕóB
	scanf("%d %d", &Rb, &Cb);
	int matrixB[Rb][Cb];
	for(i = 0; i < Rb; i++)
		for(j = 0; j < Cb; j++)
			scanf("%d", &matrixB[i][j]);
	if(Ca != Rb)
	{
		printf("Error: %d != %d", Ca, Rb);
		return 0; 
	}
	int result[Ra][Cb];
	printf("%d %d\n", Ra, Cb);
	for(i = 0; i < Ra; i++)
	{ 
		for(j = 0; j < Cb; j++)
		{
			result[i][j] = 0;
			for(k = 0; k < Ca; k++)
				result[i][j] += matrixA[i][k] * matrixB[k][j];
			if(j == Cb - 1)
				printf("%d", result[i][j]);
			else
				printf("%d ", result[i][j]); 
		}
		if(i != Ra - 1)
			putchar('\n'); 
	} 
	return 0;
}
