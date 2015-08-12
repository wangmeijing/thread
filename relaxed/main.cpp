#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true,std::memory_order_relaxed);
//    y.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
//    while (!y.load(std::memory_order_relaxed)) {

//    }
    while (!y.load(std::memory_order_acquire)) {

    }

    if(x.load(std::memory_order_relaxed))
        ++z;
    std::cout << "z = " << z << std::endl;
}

int main()
{
    x = false;
    y = false;
    z =0;

    std::thread a(write_x_then_y);
    std::thread b(read_x_then_y);

    a.join();
    b.join();

    assert(z.load() != 0);
//    return 0;
}

