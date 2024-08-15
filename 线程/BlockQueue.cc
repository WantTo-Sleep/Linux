#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>

template <typename T>
class BlockQueue
{
public:
    BlockQueue(int capacity = 4) : _capacity(capacity)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond_consumer, nullptr);
        pthread_cond_init(&_cond_producer, nullptr);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond_consumer);
        pthread_cond_destroy(&_cond_producer);
    }
    void push(const T &val)
    {
        // 同时只能有一个线程（生产者或者消费者）能访问阻塞队列
        pthread_mutex_lock(&_mutex);
        // 如果阻塞队列已经满了，消费者需要等待
        while (_que.size() == _capacity)
        {
            // 等待的时候需要传入申请到的锁，wait调用会自动释放掉这个锁
            // 以便其他进程（消费者）可以拿到这个锁来改变阻塞队列的状态
            pthread_cond_wait(&_cond_producer, &_mutex);
        }
        _que.push(val);
        // 放入数据后，唤醒消费者
        pthread_cond_signal(&_cond_consumer);
        pthread_mutex_unlock(&_mutex);
    }
    void pop(T &val)
    {
        pthread_mutex_lock(&_mutex);
        while (_que.size() == 0)
        {
            pthread_cond_wait(&_cond_consumer, &_mutex);
        }
        val = _que.front();
        _que.pop();
        pthread_cond_signal(&_cond_producer);
        pthread_mutex_unlock(&_mutex);
    }

private:
    std::queue<T> _que;
    int _capacity;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond_consumer;
    pthread_cond_t _cond_producer;
};

template <typename T>
void *Produce(void *arg)
{
    BlockQueue<T> *bq = static_cast<BlockQueue<T> *>(arg);
    while (true)
    {
        T ret = rand() % 100;
        bq->push(ret);
        std::cout << "I am Producer, I put a data: " << ret << std::endl;
        // sleep(1);
    }
}
template <typename T>
void *Consume(void *arg)
{
    BlockQueue<T> *bq = static_cast<BlockQueue<T> *>(arg);
    while (true)
    {
        T ret;
        bq->pop(ret);
        std::cout << "I am Consumer, I get a data: " << ret << std::endl;
        sleep(1);
    }
}

int main()
{
    srand((unsigned int)time(nullptr));
    BlockQueue<int> bq;
    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, nullptr, Produce<int>, &bq);
    pthread_create(&consumer, nullptr, Consume<int>, &bq);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    return 0;
}