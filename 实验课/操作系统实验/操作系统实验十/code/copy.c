#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define OK 0    // 成功
#define INPUT_ERROR 1   // 输入参数有误
#define FILE_EXIST 2    // 文件已存在
#define COPY_ERROR 3    // 复制失败
#define NOT_A_DIRECTORY 2   // 源文件不是目录
#define BUFF_SIZE 1024  // 复制文件的缓冲区大小
#define PATH_LEN 100    // 路径占的字节数最大值
#define OWN_CHANG_ERROR 01  // 属主更改失败
#define MOD_CHANG_ERROR 010 // 权限更改失败
#define FOLDER_CREAT_ERROR 1    // 文件夹创建失败

char* getFileName(char* path);
int copyFile(char* dst, char* src);
int changeAttr(char* filename, struct stat* stat);
int copyFolder(char* dst, char* src);
int copy(char* dst, char* src);

int main(int argc, char *argv[]) {
    int fd; // open函数的返回值
    char* path[2];  // path[0]-srcfile, path[1]-dstfile
    if (argc < 3) {
        printf(" - Usage: %s srcfile dstfile\n", getFileName(argv[0]));
        return INPUT_ERROR;
    }
    path[0] = argv[1];
    path[1] = argv[2];
    // 检测源文件是否目录
    fd = open(path[0], O_DIRECTORY);
    if (fd < 0) {   // 源文件不是目录
        printf("ERROR: Source file is not a directory!");
        return NOT_A_DIRECTORY;
    }
    // 检测目标文件
    if (access(path[1], F_OK) != -1) {  // 目标文件已存在
        printf("ERROR: File already exist!");
        return FILE_EXIST;
    }
    copyFolder(path[1], path[0]);    // 创建目录
    copy(path[1], path[0]);
    return OK;
}
// 复制完整目录(包含里面的文件)
int copy(char* dst, char* src) {
    int fd1, fd2;
    struct dirent* ptr;
    DIR* dir = opendir(src);
    char srcpath[PATH_LEN], dstpath[PATH_LEN];
    while ((ptr = readdir(dir)) != NULL)
    {
        // 跳过.和..目录
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        // 生成完整路径
        strcpy(srcpath, src);
        strcpy(dstpath, dst);
        if (*(srcpath + strlen(srcpath) - 1) != '/')
            strcat(srcpath, "/");
        strcat(srcpath, ptr->d_name);
        if (*(dstpath + strlen(dstpath) - 1) != '/')
            strcat(dstpath, "/");
        strcat(dstpath, ptr->d_name);
        // 判断文件类型
        fd1 = open(srcpath, O_DIRECTORY);
        if (fd1 < 0) {   // 源文件不是目录
            fd2 = open(srcpath, O_NOFOLLOW);
            if (fd2 < 0)    // 源文件是符号链接
                printf("Message: File '%s' is a soft link!");
            else    // 源文件是普通文件
                if (copyFile(dstpath, srcpath) != OK) {
                    printf("ERROR: File '%s' copy error!", srcpath);
                    return COPY_ERROR;
                }
            close(fd2);
        } else {    // 源文件是目录
            if (copyFolder(dstpath, srcpath) != OK) {
                printf("ERROR: Directory '%s' copy error!", srcpath);
                return COPY_ERROR;
            }
            if (copy(dstpath, srcpath) != OK) { // 递归复制
                return COPY_ERROR;
            }
        }
        close(fd1);
    }
    return OK;
}
// 复制文件夹(不包含里面的文件)
int copyFolder(char* dst, char* src) {
    int fd;
    struct stat srcstat;
    fd = open(src, O_NOFOLLOW | O_DIRECTORY);
    fstat(fd, &srcstat);
    close(fd);
    // 创建文件夹
    if (mkdir(dst, srcstat.st_mode) == -1) {
        printf("> %s:\n", getFileName(src));
        printf("\tERROR: Folder '%s' copy failed!\n", src);
        return FOLDER_CREAT_ERROR;
    }
    // 设置文件夹权限
    printf("> %s:\n", src);
    printf("\tFolder '%s' copied succeeded!\n", src);
    return changeAttr(dst, &srcstat);
}
// 复制文件
int copyFile(char *dst, char *src)
{
    struct stat srcstat;
    char buff[BUFF_SIZE];
    int len, fd1, fd2;
    fd1 = open(src, O_RDONLY);
    fd2 = open(dst, O_WRONLY | O_CREAT);
    fstat(fd1, &srcstat);   // 记录源文件的属性
    while ((len = read(fd1, buff, BUFF_SIZE)))
        write(fd2, buff, len);
    close(fd1);
    close(fd2);
    printf("> %s:\n", src);
    printf("\tFile '%s' copied succeeded!\n", src);
    changeAttr(dst, &srcstat);   // 修改复制后的文件属性
    return OK;
}
// 更改属主、权限等属性，返回值为OK、MOD_CHANG_ERROR、OWN_CHANG_ERROR的组合
int changeAttr(char *filename, struct stat* stat) {
    int own, mod, ret = OK;
    own = chown(filename, stat->st_uid, stat->st_gid);  // 更改文件属主
    mod = chmod(filename, stat->st_mode);   // 更改文件权限
    if (own == -1) {    // 属主更改失败
        printf("\tERROR: File '%s' owner failed to change!\n", filename);
        ret |= OWN_CHANG_ERROR;
    }
    if (mod == -1) {    // 权限更改失败
        printf("\tERROR: File '%s' mode failed to change!\n", filename);
        ret |= MOD_CHANG_ERROR;
    }
    if (mod == OK) {    // 更改成功
        printf("\tFile '%s' attribute changed succeeded!\n", filename);
    }
    return ret;
}
// 获取路径中的文件名
char* getFileName(char* path) {
    char* p = path + strlen(path) - 1;
    if (p > path && *p == '/')
        *p = '\0';  // 除根目录外，路径不以'/'结尾
    while (p > path && *(p - 1) != '/')
        p--;
    return p;
}