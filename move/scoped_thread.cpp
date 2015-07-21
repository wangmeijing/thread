#include "scoped_thread.h"
#include <iostream>

scoped_thread::scoped_thread(std::thread thread)
    :m_thread(std::move(thread))
{
    if(m_thread.joinable())
    {
        std::cout <<" scoped threda joinable" <<std::endl;
//        m_thread.join();
    }else{
        throw std::logic_error("No thread.");
    }
}

scoped_thread::~scoped_thread()
{
    m_thread.join();
    std::cout << "scoped thread join......." <<std::endl;
}

