#ifndef DANZUN_PROGRAMMETADATA_H_INCLUDED
#define DANZUN_PROGRAMMETADATA_H_INCLUDED

#include <thread>

namespace dan::pmeta {
    std::thread::id getMainThreadId();
    bool onMainThread();
}

#endif
