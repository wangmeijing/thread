#ifndef SCOPED_THREAD_H
#define SCOPED_THREAD_H

#include <thread>

class scoped_thread
{
public:
    scoped_thread(std::thread thread);

    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator= (scoped_thread const&) = delete;

    ~scoped_thread();

private:
    std::thread m_thread;
};

#endif // SCOPED_THREAD_H
