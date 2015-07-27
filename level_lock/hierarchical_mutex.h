#ifndef HIERARCHICAL_MUTEX_H
#define HIERARCHICAL_MUTEX_H

#include <mutex>
#include <stdexcept>

#define ULONG_MAX 4068

class hierarchical_mutex
{
public:
    hierarchical_mutex(unsigned long value);
    ~hierarchical_mutex();

    void lock();
    void unlock();
    bool try_lock();

private:
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long  previous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation();
    void update_hierarchy_value();
};


#endif // HIERARCHICAL_MUTEX_H
