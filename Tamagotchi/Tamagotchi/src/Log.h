#pragma once
#include <iostream>

class LOG
{
public:
    LOG() {}

    template <class T>
    LOG& operator<<(const T& msg)
    {
//#ifdef _DEBUG
        std::cout << msg;
//#endif

        return *this;
    }

    ~LOG()
    {
//#ifdef _DEBUG
        std::cout << '\n';//std::endl;
// #endif  _DEBUG
    }
};