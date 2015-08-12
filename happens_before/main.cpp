#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

using namespace std;

std::atomic<bool> data_ready(false);
std::vector<int> data;

void reader_thread()
{
    while (!data_ready.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "data[0] = " << data[0] << std::endl;
}

void writer_thread()
{
    data.push_back(12);
    data_ready = true;
}

int main()
{
    std::thread write(writer_thread);
    std::thread read(reader_thread);

    write.join();
    read.join();

    return 0;
}

