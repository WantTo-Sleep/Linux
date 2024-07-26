#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PATHNAME "./namepipe"

int main()
{
    // 1、创建命名管道
    umask(0);
    int ret = mkfifo(PATHNAME, 0700);
    if (ret == -1)
    {
        printf("errno code: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    // 2、打开命名管道
    int fd = open(PATHNAME, O_RDONLY);
    if (fd == -1)
    {
        printf("errno code: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    // 3、从管道中读取信息
    char buffer[128];
    while (true)
    {
        ssize_t r = read(fd, buffer, sizeof(buffer) - 1);
        if (r == -1)
        {
            printf("errno code: %d, %s\n", errno, strerror(errno));
            exit(1);
        }
        if (r == 0)
        {
            printf("client quit, me too!\n");
            break;
        }
        buffer[r] = 0;
        std::cout << "server: ";
        std::cout << buffer << std::endl;
    }
    close(fd);

    ret = unlink(PATHNAME);
    if (ret == -1)
    {
        printf("errno code: %d, %s\n", errno, strerror(errno));
        exit(1);
    }
    return 0;
}