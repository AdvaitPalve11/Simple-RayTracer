#include "threadPool.h"

ThreadPool::ThreadPool()
{
    unsigned int threadCount = std::thread::hardware_concurrency();

    workers.reserve(threadCount);

    for (unsigned int i = 0; i < threadCount; i++)
    {
        workers.emplace_back([this, i]()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex);

        condition.wait(lock, [this]()
        {
            return hasWork || stop;
        });

        if (stop)
            return;

        lock.unlock();

        job(i);

        finishedJobs++;

        if (finishedJobs == jobCount)
        {
            condition.notify_one();
        }
    }
});
    }
}