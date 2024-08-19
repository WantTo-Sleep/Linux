#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

namespace sjx
{
    template <typename T>
    class RingQueue
    {
    public:
        RingQueue(size_t capacity = 4) : _capacity(capacity), _produce_pos(0), _consume_pos(0)
        {
            _que.resize(capacity);
            sem_init(&_producer_sem, 0, capacity);
            sem_init(&_consumer_sem, 0, 0);
            pthread_mutex_init(&_producer_mutex, nullptr);
            pthread_mutex_init(&_consumer_mutex, nullptr);
        }
        ~RingQueue()
        {
            sem_destroy(&_producer_sem);
            sem_destroy(&_consumer_sem);
            pthread_mutex_destroy(&_producer_mutex);
            pthread_mutex_destroy(&_consumer_mutex);
        }
        void push(const T &in)
        {
            P(&_producer_sem); // P操作

            pthread_mutex_lock(&_producer_mutex);
            size_t pos = _produce_pos;
            _produce_pos = (_produce_pos + 1) % _capacity;
            pthread_mutex_unlock(&_producer_mutex);

            _que[pos] = in;

            V(&_consumer_sem); // V操作
        }
        void pop(T *out)
        {
            P(&_consumer_sem);

            pthread_mutex_lock(&_consumer_mutex);
            size_t pos = _consume_pos;
            _consume_pos = (_consume_pos + 1) % _capacity;
            pthread_mutex_unlock(&_consumer_mutex);

            *out = _que[pos];

            V(&_producer_sem);
        }

    private:
        void P(sem_t *sem)
        {
            int ret = sem_wait(sem);
            if (ret != 0)
            {
                perror("P failed ");
                exit(-1);
            }
        }
        void V(sem_t *sem)
        {
            int ret = sem_post(sem);
            if (ret != 0)
            {
                perror("V failed ");
                exit(-1);
            }
        }
        std::vector<T> _que;
        size_t _capacity;
        size_t _produce_pos;
        size_t _consume_pos;
        sem_t _producer_sem;
        sem_t _consumer_sem;
        pthread_mutex_t _producer_mutex;
        pthread_mutex_t _consumer_mutex;
    };
}