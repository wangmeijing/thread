#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

std::mutex mut;
std::condition_variable cond;
int flag = 0;

void product()
{
    std::this_thread::sleep_for(std::chrono::microseconds(2000));
    std::lock_guard<std::mutex> graud(mut);
    flag = 1;
    cond.notify_one();
    std::cout << "notify........" <<std::endl;
}

void customer()
{
    std::unique_lock<std::mutex> graud(mut);

    if(mut.try_lock())
    {
        std::cout << "mutex unlocked after unique_lock" <<std::endl;
    }else{
        std::cout <<"mutex locked after unique_lock" <<std::endl;
    }

    while(flag == 0)
    {
        std::cout << "wait........." <<std::endl;
        cond.wait(graud);
    }


    if(mut.try_lock())
    {
        std::cout << "mutex unlocked after wait" <<std::endl;
    }else{
        std::cout <<"mutex locked after wait" <<std::endl;
    }

    std::cout << "flag = " << flag << std::endl;
}

int main()
{
    std::thread t1(product);
    std::thread t2(customer);

    t1.join();
    t2.join();

    return 0;
}

