#include "func.h"
#include <chrono>
#include <thread>

func::func(int i)
    :data(i)
{
}

void func::operator ()()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

func::~func()
{
}

