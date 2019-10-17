#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>  
#include <errno.h>  
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

static struct termios stored_settings;

//函数set_disp_mode用于控制是否开启输入回显功能
//如果option为0，则关闭回显，为1则打开回显
int set_disp_mode(int fd, int option)
{
    int err;
    struct termios term;
    if (tcgetattr(fd, &term) == -1)
    {
        perror("Cannot get the attribution of the terminal");
        return 1;
    }
    if (option)
        term.c_lflag |= ECHOFLAGS;
    else
        term.c_lflag &= ~ECHOFLAGS;
    err = tcsetattr(fd, TCSAFLUSH, &term);
    if (err == -1 && err == EINTR)
    {
        perror("Cannot set the attribution of the terminal");
        return 1;
    }
    return 0;
}

void set_keypress(void)
{
    struct termios new_settings;

    tcgetattr(0, &stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0, TCSANOW, &new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0, TCSANOW, &stored_settings);
    return;
}

char Pause(char *msg)
{
    if (msg == NULL)
    {
        char message[] = "press any key to continue...";
        msg = message;
    }
    puts(msg);
    set_keypress();
    //首先关闭输出回显
    set_disp_mode(STDIN_FILENO, 0);
    char c = getchar();
    set_disp_mode(STDIN_FILENO, 1);
    reset_keypress();
    return c;
}