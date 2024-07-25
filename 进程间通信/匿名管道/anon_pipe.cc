#include <iostream>
#include <cassert>
#include <string>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    int fds[2];
    int ret = pipe(fds);
    assert(ret == 0);

    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        // 子进程，关闭写端
        ret = close(fds[1]);
        assert(ret == 0);

        // 从管道中读取数据
        while (true)
        {
            char buffer[128];
            ssize_t read_count = read(fds[0], buffer, sizeof(buffer));
            assert(read_count >= 0);
            if (read_count == 0)
            {
                std::cout << "father quit, me too!" << std::endl;
                close(fds[0]);
                exit(0);
            }
            else
            {
                buffer[read_count] = 0;
                std::cout << getpid() << ": " << buffer << std::endl;
            }
        }
    }

    // 这里是父进程，向管道中写入数据
    close(fds[0]);
    while (true)
    {
        std::string str;
        std::cout << "Please input: ";
        getline(std::cin, str);
        // std::cout << str.c_str() << std::endl;
        if (str == "quit")
        {
            close(fds[1]);
            break;
        }
        else
        {
            
            ssize_t write_count = write(fds[1], str.c_str(), str.size());
            assert(write_count >= 0);
        }
        sleep(1);
    }
    waitpid(id, nullptr, 0);

    return 0;
}