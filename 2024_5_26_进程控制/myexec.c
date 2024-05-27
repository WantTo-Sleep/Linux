#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

extern char **environ;
int main()
{
    pid_t id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("First:\n");
        // 子进程
        execl("/usr/bin/ls", "ls", "-a", "-l", "--color=auto", NULL);
        exit(1);
    }
    // 不关心子进程的退出状态
    waitpid(id, NULL, 0);

    id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("\nSecond:\n");
        // 省略路径，直接写程序的名字
        execlp("pwd", "pwd", NULL);
        exit(1);
    }
    waitpid(id, NULL, 0);

    id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("\nThird:\n");
        // 尝试执行当前路径下的自己的程序, environ是系统提供的环境变量
        execle("./mytest", "mytest", NULL, environ);
        exit(1);
    }
    waitpid(id, NULL, 0);

    id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("\nFourth:\n");
        // 函数名带v，选项参数就用数组传递
        char *const my_argv[] = { "ls", "-a", "--color=auto", NULL };
        execv("/usr/bin/ls", my_argv);
        exit(1);
    }
    waitpid(id, NULL, 0);

    id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("\nFifth:\n");
        char *const my_argv[] = { "cat", "mytest.c", NULL };
        execvp("cat", my_argv);
        perror("wrong:");
        exit(1);
    }
    waitpid(id, NULL, 0);

    id = fork();
    assert(id >= 0);
    if (id == 0)
    {
        printf("\nSixth:\n");
        char *const my_env[] = { (char*)"MYENV=11223344", NULL };
        char *const my_argv[] = { (char*)"mytest", NULL };
        execvpe("./mytest", my_argv, my_env);
        exit(1);
    }
    waitpid(id, NULL, 0);

    return 0;
}
