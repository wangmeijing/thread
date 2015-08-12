#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

//std::atomic<bool> sync1(false), sync2(false);
std::atomic<int> sync(0);
std::atomic<int> data[5];


void thread_1()
{
    data[0].store(42, std::memory_order_relaxed);
    data[1].store(21, std::memory_order_relaxed);
    data[2].store(12, std::memory_order_relaxed);
    data[3].store(9, std::memory_order_relaxed);
    data[4].store(10, std::memory_order_relaxed);

//    sync1.store(true, std::memory_order_release);
    sync.store(1,std::memory_order_release);
}

void thread_2()
{
//    while(!sync1.load(std::memory_order_acquire))
//        ;
//    sync2.store(true, std::memory_order_release);

    int expected = 1;
    bool s = sync.compare_exchange_strong(expected,2,std::memory_order_acq_rel);
    std::cout << "sync = " << sync << std::endl;
//    std::cout << "s = " << s << std::endl;
    while (!s) {
//        std::cout << "sync = " << sync << std::endl;
//        std::cout << "exp = " << expected << std::endl;

        expected = 1;
    }
}


void thread_3()
{
//    while(!sync2.load(std::memory_order_acquire))
//        ;
    while (!sync.load(std::memory_order_acquire) >= 2)
        ;
    assert(data[0].load(std::memory_order_relaxed) == 42);
    assert(data[1].load(std::memory_order_relaxed) == 21);
    assert(data[2].load(std::memory_order_relaxed) == 12);
    assert(data[3].load(std::memory_order_relaxed) == 9);
 }

int main()
{
    std::thread th1(thread_1);
    std::thread th2(thread_2);
    std::thread th3(thread_3);

    th1.join();
    th2.join();
    th3.join();

    return 0;
}

