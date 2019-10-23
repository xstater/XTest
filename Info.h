#ifndef _XTEST_INFO_H_
#define _XTEST_INFO_H_

#include <iostream>
#include <mutex>

#define INFO(...) xtest::print("[INFO]",__VA_ARGS__)
#define INFOT(...) xtest::print_thread("[INFO]",__VA_ARGS__);

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

    static std::mutex stdout_mutex;

    template <class...Args>
    void print_thread(Args&&...args){
        std::lock_guard<std::mutex> lock(stdout_mutex);
        print(std::forward<Args>(args)...);
    }
}

#endif //_XTEST_INFO_H_