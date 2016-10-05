#pragma once
#include <mutex>
#include <thread>
#include <atomic>
class FastMutex {
    FastMutex(const FastMutex&) = delete;
    FastMutex& operator=(const FastMutex&) = delete;
    FastMutex(FastMutex&&) = delete;
    FastMutex& operator=(FastMutex&&) = delete;
private:
    ::std::mutex mt;
    ::std::atomic<size_t> counter = 0;
    ::std::atomic<size_t> thcounter = 0;
    ::std::thread::id tid;
public:
    void lock();
    bool try_lock();
    void unlock();
};

