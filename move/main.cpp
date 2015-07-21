#include <iostream>
#include <utility> //std::move
#include <vector>
#include<functional>
#include<algorithm>

#include "scoped_thread.h"
#include "func.h"

using namespace std;

class test{
    public:
        test(int i=0):data(i)
        {

        }

        test(const test& one)
        {
            cout<<"copy constructor"<<endl;
            data=one.data;
        }

        test& operator=(const test& one)
        {
            cout<<"operator="<<endl;
            data=one.data;
            return *this;
        }

        ~test()
        {
            cout<<"deconstructor"<<endl;
        }

    public:
        int data;
};


void fun()
{
    cout << "thread fun." << endl;
}


std::thread g(thread f)
{
    cout << " return thread.." << endl;
    return f;
}

void oops()
{
    thread my_thread(fun);

    thread r_thread = g(std::move(my_thread));

    if(r_thread.joinable())
    {
        cout << "joinablde thread." <<endl;
        r_thread.join();
    }
}


void f()
{
    int local=0;
    func my_fun(local);

    //scoped_thread t(thread(my_fun));//这样是错误的
    thread myThread(my_fun);
    scoped_thread t(move(myThread));

    cout <<"f() exit------" <<endl;
}


void num(int i)
{
    cout <<" data = " <<i <<endl;
}


void vec()
{
    std::vector<std::thread> threads;

    for(int i = 0; i < 10; i++)
    {
        threads.push_back(std::thread(num, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main()
{
    test one(10);
    cout<<"one "<<one.data<<endl;

    test two(std::move(one));
    cout<<"tow "<<two.data<<endl;

    oops();

    f();

    vec();

    return 0;
}

