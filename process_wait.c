#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t id = fork();
    // 进程创建失败
    if (id == -1)
    {
        printf("fork fail!\n");
        exit(-1);
    }
    // 子进程
    if (id == 0)
    {
        printf("I am child process.\n");
        sleep(5);
        exit(10);
    }

    int status = 0;
    int id_wait = 0;

    id_wait = waitpid(id, &status, 0);
    
    printf("id_wait:%d, signal code:%d, exit code:%d.\n", id_wait, status & 0x7f, (status >> 8) & 0xff);

    return 0;
}
