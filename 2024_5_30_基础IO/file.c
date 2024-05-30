#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "hello"

int main()
{
    int fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        // 打开文件失败
        perror("open");
        exit(1);
    }

    const char *buf = "I like Linux!\n";
    ssize_t ret = write(fd, buf, strlen(buf));
    if (ret < 0)
    {
        // 写入文件失败
        perror("write");
        exit(1);
    }
    
    // 设置偏移量，指向文件开头，用来读取数据 
    off_t off_num = lseek(fd, 0, SEEK_SET);
    if (0 - 1 == off_num)
    {
        // 偏移量设置失败
        perror("lseek");
        exit(1);
    }
    

    char buf1[64];
    ssize_t i = read(fd, buf1, sizeof(buf1) - 1);
    if (i == -1)
    {
        perror("read");
        exit(1);
    }
    buf1[i] = 0;

    i = write(2, buf1, strlen(buf1));
    if (i == -1)
    {
        perror("write");
        exit(1);
    }

    if (0 != close(fd))
    {
        perror("close");
    }
    // C文件操作
    // FILE *my_file = fopen(FILE_NAME, "w");
    // if (!my_file)
    // {
    //     perror("fopen");
    // }
    // 
    // const char* text1 = "linux so easy!\n";
    // fwrite(text1, strlen(text1), 1, my_file);
    // fclose(my_file);

    // my_file = fopen(FILE_NAME, "r");
    // char text2[64];
    // size_t i = fread(text2, 1, sizeof(text2) - 1, my_file);
    // text2[i] = 0;
    // printf("%s", text2);

    // fclose(my_file);

    return 0;
}
