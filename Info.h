#ifndef _XTEST_INFO_H_
#define _XTEST_INFO_H_

#include <iostream>

#define INFO(...) xtest::print("[INFO]",__VA_ARGS__)

namespace xtest{
    template <class Arg>
    void print(Arg &&arg){
        std::cout << arg << std::endl;
    }
    template <class Arg,class...Args>
    void print(Arg &&arg,Args &&...args){
        std::cout << arg;
        print(std::forward<Args>(args)...);
    }
}

#endif //_XTEST_INFO_H_