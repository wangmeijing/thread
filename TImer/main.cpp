#include <iostream>
#include "timer.h"

using namespace std;

void func()
{
    cout << "Hello World!" << endl;
}

int main()
{
    TImer timer;
    func();

    cout << timer.elapsed() << endl;
    cout << timer.elapsed_micro() << endl;
    cout << timer.elapsed_nano() << endl;
    cout << timer.elapsed_seconds() << endl;
    cout << timer.elapsed_minutes() << endl;
    cout << timer.elapsed_hours() << endl;

    return 0;
}

