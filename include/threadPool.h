#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool
{
private:

    std::vector<std::thread> workers;

    std::mutex mutex;

    std::condition_variable condition;

    std::atomic<int> finishedJobs{0};

    bool stop = false;

    bool hasWork = false;

    std::function<void(int)> job;

    int jobCount = 0;

public:

    ThreadPool();

    ~ThreadPool();

    void parallelFor(
        int count,
        const std::function<void(int)>& function
    );
};