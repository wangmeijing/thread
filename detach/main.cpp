#include <iostream>
#include <thread>

using namespace std;

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

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);

    thread my_thread(my_func);
    my_thread.join();
}

int main()
{
//    oops();

    int some_local_state = 0;
    func my_func(some_local_state);

    thread my_thread(my_func);
    my_thread.join();

    return 0;
}
