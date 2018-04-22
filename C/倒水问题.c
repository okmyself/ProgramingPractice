#include <stdio.h>
#include <time.h>
typedef struct {
	int capacity;
	int current;
} Cup;
void pour(Cup *c1, Cup *c2);

int main(void)
{
	int a,b;
	Cup c[3];
	c[0].capacity = 10;
	c[0].current = 10;
	c[1].capacity = 5;
	c[1].current = 0;
	c[2].capacity = 6;
	c[2].current = 1;
	srand((unsigned)time(NULL));
	do
	{
		a = rand() % 3;
		do
			b = rand() % 3;
		while(b == a);
						printf("%d %d\n", a + 1, b + 1);
		pour(&c[a], &c[b]);

		printf("%d,%d,%d\n", c[0].current, c[1].current, c[2].current);
	} while(c[0].current != 8 && c[2].current != 8);
	return 0;
}

void pour(Cup *c1, Cup *c2)	/*c1µ¹µ½c2*/
{
	while(c1->current > 0 && c2->current < c2->capacity)
	{
		c2->current++;
		c1->current--; 
	}
}
