#include <iostream>
#include <chrono>
#include <unistd.h>
#include <future>
#include <ctime>
#include <iomanip>

using namespace std;

int main(void)
{
    std::chrono::milliseconds ms{3};

    std::chrono::microseconds us = 2 * ms;

    std::chrono::duration<double,std::ratio<1,30> > hz30{3.5};

    std::cout << "3ms duration has " << ms.count() << " ticks\n"
              << "6000us duration has " << us.count() << " ticks\n";


    typedef std::chrono::duration<int, std::ratio<60*60*24>> days_type;
    std::chrono::time_point<std::chrono::system_clock,days_type> today =
            std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
    std::cout << today.time_since_epoch().count() << " days since epoch.\n";

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t last = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::time_t next = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24));

//    std::cout << last << std::endl;

    return 0;
}

