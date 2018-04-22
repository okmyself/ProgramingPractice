#define _CRT_SECURE_NO_WARNINGS  
#define TYPE
typedef double ElemType;
#include <stdio.h>
#include "SqList.h"

void outputDouble(int i, double e)
{
	printf("%d\t%f\n", i, e);
}

Status compareDouble(ElemType a, ElemType b)
{
	return a > b;
}

int main(void)
{
	int i;
	SqList La, Lb, Lc;
	InitList_Sq(&La);
	for (i = 0; i < 10; i++)
		ListInsert_Sq(&La, i + 1, 2 * i + 1);
	printf("La:\ni\telem\n");
	PrintList_Sq(&La, outputDouble);
	
	InitList_Sq(&Lb);
	for (i = 0; i < 10; i++)
		ListInsert_Sq(&Lb, i + 1, 2 * i + 2);
	printf("Lb:\ni\telem\n");
	PrintList_Sq(&Lb, outputDouble);
	
	InitList_Sq(&Lc);
	MergeList_Sq(&La, &Lb, &Lc, compareDouble);
	printf("Lc:\ni\telem\n");
	PrintList_Sq(&Lc, outputDouble);
	return 0;
}