#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // sigprocmask() 测试
    sigset_t set, oset;
    int ret = sigemptyset(&set);
    if (ret == -1)
    {
        perror("sigemptyset");
        exit(-1);
    }
    // 阻塞2号信号和40号信号
    ret = sigaddset(&set, 2);
    if (ret == -1)
    {
        perror("sigaddset 2");
        exit(-1);
    }
    ret = sigaddset(&set, 40);
    if (ret == -1)
    {
        perror("sigaddset 40");
        exit(-1);
    }
    sigprocmask(SIG_BLOCK, &set, &oset);
    // 读取当前进程的未决信号集
    sigset_t pending;
    while (1)
    {
        ret = sigpending(&pending);
        if (ret == -1)
        {
            perror("sigpending");
            exit(-1);
        }
        printf("pid: %d. 是否收到2号信号和40号信号: ", getpid());
        if (sigismember(&pending, 2)) printf("1");
        else printf("0");
        if (sigismember(&pending, 40)) printf("1");
        else printf("0");
        printf("\n");
        sleep(1);
    }
    return 0;
}

// void sigcb(int signum)
// {
//     int cnt = 10;
//     while (cnt--)
//     {
//         printf("pid: %d, 收到了%d号信号.->%d\n", getpid(), signum, cnt);
//         sleep(1);
//     }
// }

// int main()
// {
//     // sigaction()测试
//     struct sigaction act, oact;
//     sigset_t mask; // 信号递达时需要屏蔽的信号
//     sigemptyset(&mask);
//     sigaddset(&mask, 3); // 假设处理时要屏蔽3号信号
//     act.sa_handler = sigcb;
//     act.sa_mask = mask;
//     act.sa_flags = 0;

//     int ret = sigaction(SIGINT, &act, &oact);
//     if (ret == -1)
//     {
//         perror("sigaction");
//         exit(-1);
//     }

//     printf("pid: %d正在运行...\n", getpid());
//     while (true)
//     {
//         sleep(1);
//     }

//     return 0;
// }

// int main()
// {
//     // signal()测试
//     signal(SIGINT, sigcb);

//     printf("pid: %d正在运行...\n", getpid());
//     while (true)
//     {
//         sleep(1);
//     }

//     return 0;
// }