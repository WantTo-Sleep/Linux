#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("这是另一个程序！\n");
    printf("MYENV=%s\n", getenv("MYENV")); 
    printf("PATH=%s\n", getenv("PATH"));
    return 0;
}
