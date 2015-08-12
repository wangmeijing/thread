#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;
using namespace std::chrono;

class TImer
{
public:
    TImer():
        m_begin(high_resolution_clock::now())
    {}

    ~TImer(){}

    void reset()
    {
        m_begin = high_resolution_clock::now();
    }

    template <typename Duration= milliseconds>
    int64_t elapsed() const
    {
        return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
    }

    int64_t elapsed_micro() const
    {
        return elapsed<microseconds>();
    }

    int64_t elapsed_nano() const
    {
        return elapsed<nanoseconds>();
    }

    int64_t elapsed_seconds() const
    {
        return elapsed<seconds>();
    }

    int64_t elapsed_minutes() const
    {
        return elapsed<minutes>();
    }

    int64_t elapsed_hours() const
    {
        return elapsed<hours>();
    }
private:
    time_point<high_resolution_clock> m_begin;
};

#endif // TIMER_H
