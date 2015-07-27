/*
 * 一个函数采用unique_lock加锁mutex然后准备好数据并将unique_lock返回给调用者，
 * 调用者在mutex保护下对数据进一步加工
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

std::mutex some_mutex;
std::unique_lock<std::mutex> get_lock()
{
    std::unique_lock<std::mutex> lk(some_mutex);
    std::cout << "get lock" << std::endl;
    return lk;
}

void process()
{
    std::unique_lock<std::mutex> lk(get_lock());
    std::cout << "process data..." << std::endl;
}

void f()
{

}

int main()
{
    process();
    return 0;
}

