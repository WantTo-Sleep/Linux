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
        execlp("ls", "ls", "-a", "-l", NULL);
        printf("process replace fail!\n");
        exit(-1);
    }

    int status = 0;
    int id_wait = 0;

    id_wait = waitpid(id, &status, 0);
    
    printf("id_wait:%d, signal code:%d, exit code:%d.\n", id_wait, status & 0x7f, (status >> 8) & 0xff);
    sleep(3);

    return 0;
}
