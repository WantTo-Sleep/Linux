#include "common.hpp"

int main()
{
    // 1、创建共享内存，返回共享内存id
    int id = createShm(4096);
    
    // 2、将共享内存与当前进程地址空间映射
    char* address = (char*)shmat(id, nullptr, 0);
    if ((long)address == -1)
    {
        perror("attach");
        exit(-1);
    }

    // 3、向共享内存中写入数据
    int cnt = 0;
    while (cnt < 10)
    {
        sprintf(address, "I am process server, my pid: %d, this is %d messenge!\n", getpid(), ++cnt);
        sleep(4);
    }
    sprintf(address, "quit");

    // 4、解除共享内存与当前共享内存的联系
    int id_dt = shmdt(address);
    if (id_dt == -1)
    {
        perror("detach");
        exit(-1);
    }

    // 5、删除共享内存
    int id_rm = shmctl(id, IPC_RMID, nullptr);
    if (id == -1)
    {
        perror("remove");
        exit(-1);
    }

    return 0;
}