#include "FastMutex.h"

void FastMutex::lock() { 
    ::std::thread::id ctid = ::std::this_thread::get_id();
    if (++this->counter != 1) {
        if (ctid == this->tid)
            return (void)++this->thcounter;
        else
            mt.lock();
    }
    this->tid = ctid;
    return (void)++this->thcounter;
}

bool FastMutex::try_lock() {
    return false;
}

void FastMutex::unlock() { 
}
