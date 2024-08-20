#include <ctime>
#include "ThreadPool.hpp"

void *Handler(void *arg)
{
    size_t code = (size_t)arg;
    int num1 = rand() % 100;
    int num2 = rand() % 100;
    int num3 = 0;
    char op = 0;
    switch (code % 4)
    {
    case 0:
    {
        num3 = num1 + num2;
        op = '+';
        break;
    }
    case 1:
    {
        num3 = num1 - num2;
        op = '-';
        break;
    }
    case 2:
    {
        num3 = num1 * num2;
        op = '*';
        break;
    }
    case 3:
    {
        op = '/';
        if (num2 == 0)
            printf("除0错误！\n");
        else
            num3 = num1 / num2;
    }
    break;
    }
    printf("线程id：%p，任务编号：%d，任务：%d %c %d = %d\n", pthread_self(), code, num1, op, num2, num3);
    return nullptr;
}

int main()
{
    srand((unsigned int)time(nullptr));
    sjx::ThreadPool tp;
    for (size_t i = 0; i < -1; ++i)
    {
        sjx::Task *task = new sjx::Task(Handler, (void *)i);
        tp.PushTask(task);
    }
    return 0;
}