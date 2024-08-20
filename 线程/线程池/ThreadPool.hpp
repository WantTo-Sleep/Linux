#pragma once

#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

namespace sjx
{
    typedef void *(*handler_t)(void *);
    class Task
    {
    public:
        // 要执行的任务和给任务传递的参数
        Task(handler_t handler = nullptr, void *arg = nullptr) : _handler(handler), _arg(arg)
        {
        }
        void SetTask(handler_t func, void *arg)
        {
            _handler = func;
            _arg = arg;
        }
        void *Run()
        {
            return _handler(_arg);
        }

    private:
        handler_t _handler;
        void *_arg;
    };

    class ThreadPool
    {
    public:
        ThreadPool(size_t thread_num = 4, size_t task_num = 4):_thread_num(thread_num), _task_num(task_num)
        {
            _thread.resize(_thread_num);
            for (size_t i = 0; i < _thread_num; ++i)
            {
                int ret = pthread_create(&_thread[i], nullptr, Start, (void*)this);
                if (ret != 0)
                {
                    perror("Thread Create ");
                    exit(-1);
                }
            }
            pthread_mutex_init(&_mutex, nullptr);
            pthread_cond_init(&_cond_get_task, nullptr);
            pthread_cond_init(&_cond_push_task, nullptr);
        }
        ~ThreadPool()
        {
            for (size_t i = 0; i < _thread_num; ++i)
            {
                if (0 != pthread_cancel(_thread[i]))
                {
                    perror("Thread Cancel ");
                    exit(-1);
                }
            }
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_cond_get_task);
            pthread_cond_destroy(&_cond_push_task);
        }

        static void* Start(void* arg)
        {
            ThreadPool* tp = static_cast<ThreadPool*>(arg);
            while (true)
            {
                // 不断地从任务队列中获取任务并执行
                tp->Lock();
                while (tp->Empty())
                {
                    tp->Wait();
                }
                Task* t = tp->GetTask();
                tp->WakeUpOne();
                tp->UnLock();
                sleep(1);
                t->Run();
                delete t;
            }
            return nullptr;
        }
        void PushTask(Task* task)
        {
            Lock();
            while (_task.size() >= _task_num)
            {
                pthread_cond_wait(&_cond_push_task, &_mutex);
            }
            _task.push(task);
            pthread_cond_broadcast(&_cond_get_task);
            UnLock();
        }

        void Lock()
        {
            pthread_mutex_lock(&_mutex);
        }
        void UnLock()
        {
            pthread_mutex_unlock(&_mutex);
        }
        bool Empty()
        {
            return _task.empty();
        }
        void Wait()
        {
            pthread_cond_wait(&_cond_get_task, &_mutex);
        }
        void WakeUpOne()
        {
            pthread_cond_signal(&_cond_push_task);
        }
        void WakeUpAll()
        {
            pthread_cond_broadcast(&_cond_push_task);
        }
        Task* GetTask()
        {
            Task* t = _task.front();
            _task.pop();
            return t;
        }

    private:
        std::vector<pthread_t> _thread;
        std::queue<Task*> _task;
        size_t _thread_num;
        size_t _task_num;
        pthread_mutex_t _mutex;
        pthread_cond_t _cond_get_task;
        pthread_cond_t _cond_push_task;
    };
}