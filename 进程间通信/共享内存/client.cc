#include "common.hpp"

int main()
{
    // 1、打开共享内存
    int id = getShm(4096);

    // 2、将共享内存与当前进程地址空间映射
    char* address = (char*)shmat(id, nullptr, 0);
    if ((long)address == -1)
    {
        perror("attach");
        exit(-1);
    }

    // 3、从共享内存中读取数据
    while (true)
    {
        if (strcmp("quit", address) == 0)
        {
            printf("server quit! cilent too!\n");
            break;
        }
        else
        {
            printf("%s", address);
            sleep(4);
        }
    }

    // 4、解除共享内存与当前共享内存的联系
    int id_dt = shmdt(address);
    if (id_dt == -1)
    {
        perror("detach");
        exit(-1);
    }

    return 0;
}