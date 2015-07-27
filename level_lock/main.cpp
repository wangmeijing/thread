#include <iostream>
#include <thread>
#include "hierarchical_mutex.h"

using namespace std;

hierarchical_mutex high_level_mutew(1000);
hierarchical_mutex low_level_mutex(500);

int do_low_level_stuff()
{
    std::cout <<" do low level stuff." <<endl;
    return 2;
}

int low_level_func()
{
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff()
{
    cout <<"high level stuff." << endl;
}

void high_level_func()
{
    std::lock_guard<hierarchical_mutex> lk(high_level_mutew);
    high_level_stuff();
}

void thread_a()
{
    high_level_func();
}

hierarchical_mutex other_mutex(3);

void do_other_stuff()
{
    cout << "do other stuff." << endl;
}

void other_stuff()
{
//    high_level_func();
    do_other_stuff();
}


void thread_b()
{
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

int main()
{
    std::thread A(thread_a);
    std::thread B(thread_b);

    A.join();
    B.join();

    return 0;
}

