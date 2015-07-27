#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class bank_account {
public:
    bank_account(string name, int money)
        :m_name(name),
         m_money(money)
    {
    }

    string m_name;
    int m_money;
    std::mutex m_mutex;
};

void transform(bank_account &from, bank_account &to, int money)
{
    std::unique_lock<std::mutex> lock_from(from.m_mutex, defer_lock);
    std::unique_lock<std::mutex> lock_to(to.m_mutex, defer_lock);
    std::lock(lock_from, lock_to);

    std::cout << "Begin, "<< std::endl;
    std::cout << from.m_name << " $" << from.m_money << std::endl;
    std::cout <<to.m_name <<" $ " << to.m_money << std::endl;

    to.m_money += money;
    from.m_money -= money;

    std::cout << "Now, " << money << " from xx to ww" << std::endl;
    std::cout << from.m_name << " $" << from.m_money << std::endl;
    std::cout <<to.m_name <<" $ " << to.m_money << std::endl;
}

int main()
{
    bank_account w("wang", 100);
    bank_account x("xiao", 20);

    std::thread t1(transform, ref(w), ref(x), 20);
    std::thread t2(transform, ref(x), ref(w), 40);

//    std::thread t1(transform, w, x, 20);
//    std::thread t2(transform, ref(x), ref(w), 40);

//    std::thread t1(transform, std::move(w), std::move(x), 20);
//    std::thread t2(transform, std::move(x), std::move(w), 2);

    t1.join();
    t2.join();

    //lock针对mutex加锁
//    std::mutex one, two;

//    try {
//        lock(one, two);
//        throw 1;
//        std::cout << "lock..............."<<std::endl;
//    }catch(int)
//    {
//        std::cout << "catch.................." <<std::endl;
//    }

//    if(!one.try_lock() && !two.try_lock())
//        std::cout << "success";
//    else
//        std::cout << "failed";

    return 0;
}

