//#include <iostream>
//#include <atomic>
//#include <thread>
//#include <vector>
//#include <sstream>

//std::atomic_flag flag_stream = ATOMIC_FLAG_INIT;
//std::stringstream stream;

//void append_number(int i)
//{
//    while(flag_stream.test_and_set())
//    {}

//    stream << "thread # " << i << std::endl;

//    flag_stream.jclear();
//}

//using namespace std;

//int main()
//{
//    std::vector<std::thread> threads;

//     for (int i=1; i<=10; ++i)
//        threads.push_back(std::thread(append_number,i));

//     for (auto& th : threads)
//         th.join();

//     std::cout << stream.str();

//    return 0;
//}



#include <iostream>              // std::cout
#include <atomic>                // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>                // std::thread, std::this_thread::yield
#include <vector>                // std::vector

std::atomic<bool> ready(false);    // can be checked without being set
std::atomic_flag winner = ATOMIC_FLAG_INIT;    // always set when checked

void count1m(int id)
{
    while (!ready) {
        std::this_thread::yield();
    } // 等待主线程中设置 ready 为 true.

    for (int i = 0; i < 1000000; ++i) {
    } // 计数.

    // 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
    // 此后其他线程执行 test_and_set 是 if 语句判断为 false，
    // 因此不会输出自身 ID.
    if (!winner.test_and_set()) {
        std::cout << "thread #" << id << " won!\n";
    }

}

int main()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";

    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(count1m, i));

    ready = true;

    for (auto & th:threads)
        th.join();

    return 0;
}


//#include <thread>
//#include <vector>
//#include <iostream>
//#include <atomic>

//std::atomic_flag lock = ATOMIC_FLAG_INIT;

//void f(int n)
//{
//    for (int cnt = 0; cnt < 1; ++cnt) {
//        while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
//             ; // spin
//        std::cout << "Output from thread " << n << '\n';
//        lock.clear(std::memory_order_release);               // release lock
//    }
//}

//int main()
//{
//    std::vector<std::thread> v;
//    for (int n = 0; n < 10; ++n) {
//        v.emplace_back(f, n);
//    }
//    for (auto& t : v) {
//        t.join();
//    }
//}


//#include <iostream>             // std::cout
//#include <atomic>               // std::atomic
//#include <thread>               // std::thread, std::this_thread::yield

//std::atomic <int> foo(0);

//void set_foo(int x)
//{
//    foo = x; // 调用 std::atomic::operator=().
//}

//void print_foo()
//{
//    while (foo == 0) { // wait while foo == 0
//        std::this_thread::yield();
//    }
//    std::cout << "foo: " << foo << '\n';
//}

//int main()
//{
//    std::thread first(print_foo);
//    std::thread second(set_foo, 10);
//    first.join();
//    second.join();
//    return 0;
//}


//#include <iostream>       // std::cout
//#include <atomic>         // std::atomic, std::memory_order_relaxed
//#include <thread>         // std::thread

//std::atomic<int> foo(0); // 全局的原子对象 foo
//std::atomic<int> bar(0);

//void set_foo(int x)
//{
//    foo = x;
////    foo.store(x, std::memory_order_relaxed); // 设置(store) 原子对象 foo 的值
//}

//void copy_foo_to_bar()
//{
//    while (foo == 0) {
//        std::this_thread::yield();
//    }

//    bar = static_cast<int> (foo);
//}

//void parint_bar()
//{
//    while (bar == 0) {
//        std::this_thread::yield();
//    }
//    std::cout << "bar: " << bar <<std::endl;
//}

//void print_foo()
//{
//    int x;
//    do {
//        x = foo.load(std::memory_order_relaxed); // 读取(load) 原子对象 foo 的值
//    } while (x == 0);
//    std::cout << "foo: " << x << std::endl;
//}

//int main ()
//{
//    std::thread first(print_foo); // 线程 first 打印 foo 的值
//    std::thread second(set_foo, 10); // 线程 second 设置 foo 的值
//    std::thread bar(copy_foo_to_bar);
//    std::thread print(parint_bar);

//    first.join();
//    second.join();
//    bar.join();
//    print.join();

//    return 0;
//}
