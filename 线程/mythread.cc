#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <unistd.h>
#include <pthread.h>

// 条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *rout1(void *arg)
{
    while (true)
    {
        // 先申请锁
        pthread_mutex_lock(&mutex);
        // 申请到之后输出
        printf("我是线程a!\n");
        // 给线程b发信号，让它输出
        pthread_cond_signal(&cond);
        // 输出之后自己陷入等待，等待的同时锁会自动释放，这时线程b就可以申请到
        // 等待b执行完后唤醒自己
        pthread_cond_wait(&cond, &mutex);
        // 醒来之后休眠一下，休眠的时候线程b正在等待我们再一次唤醒它
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void *rout2(void *arg)
{
    while (true)
    {
        // b申请到锁之后输出
        pthread_mutex_lock(&mutex);
        printf("我是线程b!\n");
        // 输出完成唤醒a，并释放自己的锁
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, nullptr, rout1, nullptr);
    pthread_create(&tid2, nullptr, rout2, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}

// 线程互斥
// int tickets = 50;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void *GrabTicket(void *arg)
// {
//     const char *buf = static_cast<const char *>(arg);
//     while (true)
//     {
//         pthread_mutex_lock(&mutex);
//         if (tickets > 0)
//         {
//             printf("%s%d\n", buf, tickets);
//             --tickets;
//         }
//         else
//         {
//             pthread_mutex_unlock(&mutex);
//             break;
//         }
//         pthread_mutex_unlock(&mutex);
//         // 抢完票之后todo...
//         sleep(1);
//     }
//     delete[] buf;
//     return nullptr;
// }
// int main()
// {
//     std::vector<pthread_t> tids;
//     // 创建线程
//     for (int i = 0; i < 4; ++i)
//     {
//         pthread_t tid;
//         char *buf = new char[64];
//         int ret = snprintf(buf, 64, "thread %d, grab ticket: ", i + 1);
//         buf[ret] = 0;
//         pthread_create(&tid, nullptr, GrabTicket, buf);
//         tids.push_back(tid);
//     }
//     // 等待线程
//     for (int i = 0; i < 4; ++i)
//     {
//         pthread_join(tids[i], nullptr);
//     }
//     // pthread_mutex_destroy(&mutex);

//     return 0;
// }

// 线程分离
// void *rout(void *arg)
// {
//     while (true)
//     {
//         printf("I am thread: %p.\n", pthread_self());
//         sleep(1);
//     }
//     return nullptr;
// }

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid, nullptr, rout, nullptr);

//     // pthread_detach(tid);
//     sleep(5);
//     // 如果线程没有分离，会一直等到线程退出才执行if语句
//     if (pthread_join(tid, nullptr) == 0)
//     {
//         printf("pthread_join success!\n");
//     }
//     else
//     {
//         perror("pthread_join fail");
//     }
//     printf("main thread will return!\n");

//     return 0;
// }

// 线程等待
// void *rout(void *arg)
// {
//     const char *str = static_cast<const char *>(arg);
//     int len = strlen(str);
//     for (int i = 0; i < 9; ++i)
//     {
//         printf("%s\n", str);
//         sleep(1);
//     }
//     std::string *ret = new std::string;
//     *ret = "return";
//     if (str[len - 1] == '2')
//     {
//         *ret = "pthread_exit()";
//         pthread_exit(ret);
//     }
//     else if (str[len - 1] == '3')
//     {
//         while (true)
//         {
//             printf("wait main thread call pthread_cancel..\n");
//             sleep(1);
//         }
//     }
//     return ret;
// }

// int main()
// {
//     std::vector<pthread_t> tids;
//     // 线程创建
//     for (int i = 0; i < 3; ++i)
//     {
//         pthread_t tid;
//         char *buf = new char[64];
//         int ret = snprintf(buf, 64, "I am thread: %d", i + 1);
//         buf[ret] = 0;
//         pthread_create(&tid, nullptr, rout, buf);
//         tids.push_back(tid);
//     }
//     // 3种线程退出方式
//     for (int i = 0; i < 3; ++i)
//     {
//         sleep(1);
//         if (i == 2)
//         {
//             sleep(5);
//             pthread_cancel(tids[2]);
//         }
//         std::string *str = new std::string;
//         pthread_join(tids[i], (void**)&str);
//         if (str != PTHREAD_CANCELED)
//             printf("%s\n", str->c_str());
//         else
//             printf("pthread_cancel\n");
//     }

//     return 0;
// }

// void *rout(void *arg)
// {
//     int i;
//     for (;;)
//     {
//         printf("I am thread, my tid : %p.\n", pthread_self());
//         sleep(1);
//     }
// }

// int main()
// {
//     pthread_t tid;
//     int ret;
//     if ((ret = pthread_create(&tid, nullptr, rout, nullptr)) != 0)
//     {
//         fprintf(stderr, "pthread_create : %s\n", strerror(ret));
//         exit(EXIT_FAILURE);
//     }

//     int i;
//     for (;;)
//     {
//         printf("I am main thread, my tid : %p.\n", pthread_self());
//         sleep(1);
//     }
//     return 0;
// }