#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD_MAX_LEN 1000

void split(char* command, char* cw, char* args);
void myGets(char* buff);

static char * cst[] = {"dir", "cop", "era", "dis", "end"};	//reserved words array
static char * scwt[] = {"ls -l", "cp", "rm", "echo", "exit"};	//shell command array

int main(void)
{
    int i = 0;
    char command[CMD_MAX_LEN];	//input command
    char cw[CMD_MAX_LEN], args[CMD_MAX_LEN];	//command word, command args
    char destCommand[CMD_MAX_LEN];	//shell command word & args
    int len = sizeof(cst) / sizeof(char *);	//number of cst elements
    printf(">>> ");	//prompt
    myGets(command);
    while(strcmp(command, "end"))
    {
        split(command, cw, args);
        for(i = 0; i < len; i++)
        {
            if(!strcmp(cst[i], cw))
            {
                destCommand[0] = '\0';
                strcpy(destCommand, scwt[i]);
                strcat(destCommand, " ");
                strcat(destCommand, args);
                system(destCommand);
                break;
            }
        }
        if(i == len)
            printf("No command named \"%s\".\n", cw);
        printf(">>> ");
        myGets(command);
    }
    return 0;
}

void myGets(char* buff)
//filter out line break after using fgets
{
    int i = 0;
    fgets(buff, CMD_MAX_LEN, stdin);
    //filter out line break
    while(*(buff + i) != '\0' && *(buff + i) != '\n') i++;
    *(buff + i) = '\0';
}

void split(char* command, char* cw, char* args)
//split command into command word and args
{
    int i = 0, pos1, pos2, pos;
    //skip leading blanks
    while(*command == ' ' || *command == '\t') command++;
    //find the first blank after the command word
    pos1 = strcspn(command, " ");
    pos2 = strcspn(command, "\t");
    pos = pos1 > pos2 ? pos2 : pos1;
    //save the result
    for(i = 0; i < pos; i++)
    {
        *cw = *(command + i);
        cw++;
    }
    *cw = '\0';
    if(strlen(command) <= pos)
        *args = '\0';
    else
    {
        command += pos + 1;
        strcpy(args, command);
    }
}
