#include <iostream>
#include <thread>

using namespace std;
void do_some_work()
{
    std::cout <<" child thread do some work." <<std::endl;
}


class backgraund_task
{
public:
    backgraund_task() {}

    void operator ()() const
    {
        std::cout << "class do some work" <<std::endl;
        std::cout << "class do something else" <<std::endl;
    }
};
int main()
{

    //传入函数
    std::thread my_thread(do_some_work);

    //传入类，复制对象到新创建的线程
    backgraund_task t;
    std::thread bask_thread(t);
//    std::thread bask_thread1((backgraund_task()));
    std::thread bask_thread1{(backgraund_task())};

    //lambda
    std::thread lambda_thread([]{
                              std::cout << " lambda thread" << std::endl;});

    std::cout << "main thread..."  << std::endl;

    my_thread.join();
    bask_thread.join();
    bask_thread1.join();
    lambda_thread.join();

    return 0;
}




