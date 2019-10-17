#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1000
#define ERROR 1
#define WORD_MAX_LEN 10

char toLower(char ch);
int FindWord(char *str, char *word, int ignoreCase, int *curpos, int *curline);
int isWord(char ch);

int main(void)
{
    char ch[2], buffer[BUFF_SIZE] = { 0 };
    char *s = buffer;
    char word[WORD_MAX_LEN];
    ch[1] = '\0';                       //设置字符串的长度为1
    
    FILE *fp = fopen("text.txt", "w");  //以只写方式打开文件，如果不存在在创建
    if(fp == 0) return ERROR;
    printf("请输入文件内容(以$结束)：\n");
    while((ch[0] = getchar()) != '$')
        strcat(s, ch);
    while(getchar() != '\n') ;          //过滤掉多输入的内容
    fwrite(s, sizeof(char), strlen(s), fp);
    fclose(fp);
    
    fp = fopen("text.txt", "r");
    if(fp == 0) return ERROR;
    fseek(fp, 0, SEEK_SET);
    long begin = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    long filesize = end - begin;
    printf("请输入您要查找的单词：");
    scanf("%s", word);
    fread(s, sizeof(char), filesize / sizeof(char), fp);
    int curpos = 0, curline = 0, times = 0;
    int pos = FindWord(s, word, 1, &curpos, &curline);
    if(pos == -1)
        printf("文件中未出现单词%s\n", word);
    else
    {
        printf("首次出现%s的行号为：%d，位置为：%d（行号和位置均从0开始）\n", word, curline, pos);
        while(pos != -1)
        {
            pos = FindWord(s, word, 1, &curpos, &curline);
            times++;
        }
        printf("出现的次数为：%d\n", times);
    }
    
    fclose(fp);
    return 0;
}

int FindWord(char *str, char *word, int ignoreCase, int *curpos, int *curline)
{
    int wordStart = -1;                 //-1表示不是单词开头
    int offset;
    if(isWord(*(str + *curpos))) wordStart = *curpos;
    while(*(str + *curpos) != '\0')
    {
        if(*(str + *curpos) == '\n') (*curline)++;
        if(wordStart != -1)
        {
            offset = 0;
            while(isWord(*(str + *curpos)) && isWord(*(word + offset)))
            {
                if(ignoreCase &&
                   toLower(*(str + *curpos)) != toLower(*(word + offset)) &&
                   *(word + offset) != '\0')
                {
                    wordStart = -1;
                    break;
                }
                if(!ignoreCase &&
                   *(str + *curpos) != *(word + offset) &&
                   *(word + offset) != '\0')
                {
                    wordStart = -1;
                    break;
                }
                (*curpos)++;
                offset++;
            }
            if(wordStart != -1 && *(word + offset) == '\0' && !isWord(*(str + *curpos)))
                return wordStart;
            wordStart = -1;
        }

        (*curpos)++;
        if(wordStart == -1)
        {
            if(!isWord(*(str + *curpos - 1)) && isWord(*(str + *curpos)))
                wordStart = *curpos;
        }
    }
    
    return -1;                          //未找到
}

char toLower(char ch)
{
    return ch | 0x20;
}

int isWord(char ch)
{
    if(ch >= 'a' && ch <= 'z') return 1;
    if(ch >= 'A' && ch <= 'Z') return 1;
    return 0;
}
