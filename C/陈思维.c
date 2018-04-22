#include <stdio.h>

int main(void)
{
	//输入一个字符，如果是小写字母，将小写字母加2，
	//如果是大写字母，将大写字母加3，
	//对于操作范围的字母进行循环，
	//比如字符y，y+2超过了小写字母的范围，那么把y变成a， 
	//相应的z变为b，大写字母同理
	char ch;
	while(1)
	{
		scanf("%c", &ch);
		if(ch < 'A' || ch > 'z')
			break;
		else if(ch > 'Z' && ch < 'a')
			break;
		else
		{
			if(ch + 2 > 'z')
				ch = ch - 'z' + 'a' - 1;
			else if(ch <= 'Z' && ch + 2 > 'Z')
				ch = ch - 'Z' + 'A' - 1;
			else
				ch += 2;
		}
		printf("%c\n", ch);
	}
	return 0;
}
