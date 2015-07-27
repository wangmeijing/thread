#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std;

class some_big_object {
public:
    some_big_object(int data):
        m_data(data)
    {}
    int m_data;
};

void swap(some_big_object lhs, some_big_object rhs)
{
    sleep(1);
    std::cout << "sawp(" << lhs.m_data << ", " <<rhs.m_data <<" )" <<std::endl;

    int temp;
    temp = lhs.m_data;
    lhs.m_data = rhs.m_data;
    rhs.m_data = temp;

    std::cout << "After sawp(" << lhs.m_data << ", " <<rhs.m_data <<" )" <<std::endl;
}

class X {
public:
    X(some_big_object sd):
        some_detail(sd)
    {}

    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs == &rhs)
            return;

        //使用lock_guard,adopt_lock
//        std::lock(lhs.m_mutex, rhs.m_mutex);
//        std::lock_guard<std::mutex> lock_a(lhs.m_mutex, std::adopt_lock);
//        std::lock_guard<std::mutex> lock_b(rhs.m_mutex, std::adopt_lock);

        //使用unique_guard,defer_lock
        std::unique_lock<std::mutex> lock_a(lhs.m_mutex, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m_mutex, std::defer_lock);
        std::lock(lock_a, lock_b);

        swap(lhs.some_detail, rhs.some_detail);
    }

private:
    some_big_object some_detail;
    std::mutex m_mutex;
};


void threadFUn(X &one, X&two)
{
    swap(one, two);
}

//void threadFUn(some_big_object &one, some_big_object &two)
//{
//    swap(one, two);
//}

int main()
{
    some_big_object one(10), two(20);
    X th1(one), th2(two);

    std::thread threadOne(threadFUn, ref(th1), ref(th2));
    std::thread threadTwo(threadFUn, ref(th2), ref(th1));

//    std::thread threadOne(threadFUn, ref(one), ref(two));
//    std::thread threadTwo(threadFUn, ref(two), ref(one));

    threadOne.join();
    threadTwo.join();

    return 0;
}

