#include <stdio.h>

typedef struct {
	char name[11];
	char number[11];
	int score;
} stu;

int main(void)
{
	int i, n;
	stu max, min, temp;
	max.score = 0;
	min.score = 100;
	
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%s %s %d", temp.name, temp.number, &temp.score);
		if(temp.score <= min.score)
			min = temp;
		if(temp.score >= max.score)
			max = temp;
	}
	printf("%s %s\n%s %s", max.name, max.number, min.name, min.number);
}
