#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    // 测试非阻塞等待
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork fail");
        exit(1);
    }

    if (id == 0)
    {
        // child
        int cnt = 5;
        while(cnt--)
        {
            printf("I'm child, pid:%d, ppid:%d, cnt=%d\n", getpid(), getppid(), cnt);
            sleep(1);
        }
        exit(10);
     }
    if (id > 0)
    {
        // parent
        int status = 0;
        while (1)
        {
            int ret = waitpid(id, &status, WNOHANG);
            if (ret == 0)
            {
                printf("子进程未退出，于是父进程去做其他事了...\n");
                sleep(1);
            }
            else if (WIFEXITED(status))
            {
                // 正常退出
                // 退出码应为10（上面设置的）
                printf("子进程正常退出, exit code: %d\n", WEXITSTATUS(status));
                exit(0);
            }
            else if (WIFSIGNALED(status))
            {
                // 异常退出
                int sig_code = WTERMSIG(status);
                printf("子进程异常退出, signal code: %d\n", sig_code);
                printf("%s\n", strerror(sig_code));
                exit(0);
            }
        }
    }
    
    // 测试waitpid()和status
    // pid_t id = fork();
    // if (id < 0)
    // {
    //     perror("fork fail");
    //     exit(1);
    // }

    // if (id == 0)
    // {
    //     // child
    //     int cnt = 5;
    //     while(cnt--)
    //     {
    //         printf("I'm child, pid:%d, ppid:%d, cnt=%d\n", getpid(), getppid(), cnt);
    //         sleep(1);
    //         if (cnt == 1)
    //         {
    //             // 这里空指针访问会异常退出
    //             int *p = NULL;
    //             *p = 10;
    //         }
    //     }
    //     exit(10);
    //  }
    // if (id > 0)
    // {
    //     // parent
    //     int status = 0;
    //     int ret = waitpid(id, &status, 0);
    //     if (ret > 0 && (status & 0x7F) == 0)
    //     {
    //         // 正常退出
    //         // 退出码应为10（上面设置的）
    //         printf("exit code: %d\n", (status >> 8) & 0xFF);
    //     }
    //     else if (ret > 0)
    //     {
    //         // 异常退出
    //         int sig_code = status & 0x7F;
    //         printf("signal code: %d\n", sig_code);
    //         printf("%s\n", strerror(sig_code));
    //         
    //     }
    // }
    
    // 测试wait()
    // pid_t id = fork();

    // if (id < 0)
    // {
    //     perror("fork fail");
    //     exit(1);
    // }
    // 
    // if (id == 0)
    // {
    //     // child
    //     int cnt = 5;
    //     while(cnt--)
    //     {
    //         printf("I'm child, pid:%d, ppid:%d, cnt=%d\n", getpid(), getppid(), cnt);
    //         sleep(1);
    //     }
    //     exit(10);
    // }

    // if (id > 0)
    // {
    //     wait(NULL);
    //     printf("wait success!\n");
    // }


    // 测试_exit()和exit()的区别
    // printf("hello world");
    // // _exit(0);

    // exit(0);
    
    return 0;
}
