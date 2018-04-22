#include <stdio.h>
int getCommonDivisor(int n1, int n2);
int getCommonMultiple(int n1, int n2);

int main(void)
{
	printf("%d", getCommonMultiple(1234567, 1234567));
	return 0;
}

int getCommonDivisor(int n1, int n2)
{
	int temp;
	do
	{
		if(n1 < n2)
		{
			temp = n1;
			n1 = n2;
			n2 = temp;
		}
		temp = n2;
		n2 = n1 % n2;
		n1 = temp;
	} while(n2 != 0);
	return n1;
}

int getCommonMultiple(int n1, int n2)
{
	int commonDivisor = getCommonDivisor(n1, n2);
	n1 /= commonDivisor;
	return n1 * n2;
}
