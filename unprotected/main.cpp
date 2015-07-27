#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include<functional>
#include<algorithm>

using namespace std;

class some_data{
public:
    void do_something(){
//        std::lock_guard<std::mutex> l(m);
        data++;
        std::cout << "some_data.data: " <<data <<std::endl;
    }

private:
    int data = 5;
//    std::mutex m;
};

class data_wrapper {
public:
    template<typename Fun>
    void process_data(Fun func)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        func(data);
        data.do_something();
    }

private:
    some_data data;
    std::mutex m_mutex;
};

some_data data;
void malicious_function(some_data protected_data)
{
    data = protected_data;
}

//数据不一致
//some_data *data;
//void malicious_function(some_data &protected_data)
//{
//    data = &protected_data;
//}

data_wrapper X;

void do_work(int i)
{
    std::cout << "i = " << i << std::endl;
}

void f()
{
    std::vector<std::thread> threads;
    for(unsigned i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

}


int main(void)
{
    std::thread th(&some_data::do_something, &data);
    X.process_data(malicious_function);
    data.do_something();

    th.join();

    f();

    return 0;
}


