#include <thread>
#include <iostream>
#include <list>
#include <algorithm>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    std::cout << "kkkkkk" << *std::find(some_list.begin(), some_list.end(),value_to_find) << std::endl;

    return std::find(some_list.begin(), some_list.end(),
                     value_to_find) != some_list.end();
}

int main(void)
{
    some_list.push_back(10);
    some_list.push_back(20);
    some_list.push_back(4);

    for(auto &i: some_list)
        std::cout << i << std::endl;

    std::thread my_thread1(add_to_list, 16);
    std::thread my_thread2(add_to_list, 3);

    std::thread find_thread(list_contains,3);

    my_thread1.join();
    my_thread2.join();
    find_thread.join();

    std::cout << "after inster number: " <<std::endl;
    for(auto &i: some_list)
        std::cout << i << std::endl;

    return 0;
}
