#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_COMMAND 128
#define NUM_OPTION 32

char command_line[NUM_COMMAND] = { 0 };
char *option[NUM_OPTION] = { 0 };
int main()
{
    while (1)
    {
        printf("[%s@%s 当前路径] $ ", getenv("USER"), getenv("HOSTNAME"));
        fflush(stdout);
        // 读取命令行输入到command_line中
        fgets(command_line, NUM_COMMAND - 1, stdin);
        // 读入的换行符改成'\0'
        command_line[strlen(command_line) - 1] = 0;

        // 将读入的命令分割开来，如"ls -a -l"->"ls" "-a" "-l" NULL
        option[0] = strtok(command_line, " ");
        int i = 1;
        while ((option[i++] = strtok(NULL, " ")) != NULL);
        
        // 内建(内置)命令 cd 
        if (option[0] != NULL && strcmp(option[0], "cd") == 0)
        {
            if (option[1] != NULL)
            {
                chdir(option[1]);
            }
            continue;
        }

        // 让子进程来执行命令
        pid_t id = fork();
        assert(id >= 0);
        
        if (id == 0)
        {
            execvp(option[0], option);
            exit(1);
        }
        waitpid(id, NULL, 0);
    }
    return 0;
}
