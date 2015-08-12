#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

std::atomic<bool> x(false), y(false);
std::atomic<int> z(0);

void write_x()
{
//    x.store(true, std::memory_order_seq_cst);
    x.store(true, std::memory_order_release);
}

void write_y()
{
//    y.store(true, std::memory_order_seq_cst);
    y.store(true, std::memory_order_release);
}

void read_x_then_y()
{
//    while (!x.load(std::memory_order_seq_cst))
//    {
//    }
    while (!x.load(std::memory_order_acquire)) {

    }

    std::cout << "read X........" << std::endl;

//    if(y.load(std::memory_order_seq_cst))
    if(y.load(std::memory_order_acquire))
        ++z;

//    std::cout << "z = " << z << std::endl;
}

void read_y_then_x()
{
//    while (!y.load(std::memory_order_seq_cst))
//    {
//    }
    while (!y.load(std::memory_order_acquire)) {

    }

    std::cout << "read y........" << std::endl;

//    if(x.load(std::memory_order_seq_cst))
    if(x.load(std::memory_order_acquire))
        ++z;

//    std::cout << "z = " << z << std::endl;
}

int main()
{
//    x = false;
//    y = false;
//    z = 0;

    std::thread th1(write_x);
    std::thread th2(write_y);
    std::thread th3(read_x_then_y);
    std::thread th4(read_y_then_x);

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    std::cout << "z = " << z << std::endl;

    assert(z.load() != 0);
    return 0;
}

