#include <iostream>
#include <future>
#include <thread>
#include <algorithm>

using namespace std;

double square_root(double x)
{
    if(x < 0)
        throw std::out_of_range("x < 0");

    return sqrt(x);
}


void s(std::future<double>& fut)
{
    double x = fut.get();
    std::cout << " fut = " << x << std::endl;
}

int main()
{
    std::thread f1(square_root, 4.0);

    double y = square_root(4.0);

    std::future<double> f =std::async(square_root, 4.0);
    double x = f.get();

    std::packaged_task<double(double)> myPackage(square_root);
    std::future<double> p = myPackage.get_future();
    std::thread f2(std::move(myPackage),4.0);


    std::promise<double> prom;
    std::future<double> m = prom.get_future();
    std::thread f3(square_root,4.0);
    prom.set_value(4.0);



    std::cout << " y = " << y << std::endl;
    std::cout << " x = " << x << std::endl;
    std::cout << " p = " << p.get() << std::endl;
    std::cout << " m = " << m.get() << std::endl;

    f1.join();
    f2.join();
    f3.join();

    return 0;
}

