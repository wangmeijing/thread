#include <iostream>
#include <thread>

using namespace std;

class thread_guard
{
public:
    explicit thread_guard(std::thread &t):
        m_thread(t)
    {

    }

    ~thread_guard()
    {
        if(m_thread.joinable())
            m_thread.join();
    }


private:
    std::thread &m_thread;
};

class func
{
public:
    func(int &i):
        m_i(i)
    {}

    void operator ()()
    {
        for(int i = 0; i < 100; i++)
        {
            cout << "times: " << i << std::endl;
        }
    }

private:
    int &m_i;
};

void do_something_in_current_thread()
{
    cout << "I is current thread." <<endl;
}


void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);

    thread my_thread(my_func);
    //........确保do_something_in_current_thread()退出之后调用join  .....//

    //.............method 1...............//

//    try{
//         do_something_in_current_thread();
//        }
//    catch(...)
//    {
//        my_thread.join();//确保在异常条件下join子线程
//        throw;
//    }
//    my_thread.join();

    //.............method 2...............//
    thread_guard g_thread(my_thread);
    do_something_in_current_thread();
}

int main()
{
    oops();

    return 0;
}
