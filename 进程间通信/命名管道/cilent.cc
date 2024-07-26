#include <iostream>
#include <string>
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
    // 1、打开命名管道
    int fd = open(PATHNAME, O_WRONLY);
    if (fd == -1)
    {
        printf("errno code: %d, %s\n", errno, strerror(errno));
        exit(1);
    }

    // 2、向管道中输入信息
    std::string str;
    while (true)
    {
        std::cout << "client: ";
        getline(std::cin, str);
        if (str == "quit")
        {
            printf("client quit!\n");
            break;
        }
        ssize_t r = write(fd, str.c_str(), str.size());
        if (r == -1)
        {
            printf("errno code: %d, %s\n", errno, strerror(errno));
            exit(1);
        }
    }
    close(fd);

    return 0;
}