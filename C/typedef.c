#include <stdio.h>
typedef int ElemType;
typedef struct {
	ElemType data;
} S;
int main(void)
{
	S a, b;
	char str[] = "abcde";
	
	a.data = str;
	printf("%s\n",a.data);
	
	typedef char* ElemType;
	b.data = str;
	printf("%s",b.data);
	
	return 0;
}
