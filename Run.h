#ifndef _XTEST_RUN_H_
#define _XTEST_RUN_H_

#include <chrono>
#include <iostream>
#include "Utility.h"

namespace xtest{
    template <class Function>
    void call(Function &&function){
        function();
    }
    template <class Function,class...Functions>
    void call(Function &&function,Functions&&...functions){
        function();
        call(std::forward<Functions>(functions)...);
    }

}

#define REPEAT(func,count) \
[]()->void{ \
    std::cout << "Loop:" << std::endl; \
    std::chrono::duration<double> total; \
    unsigned int passed_cnt = 0; \
    for(unsigned int i = 0;i < count;++i){ \
        auto result = func(); \
        total += result.time; \
        if(result.pass) \
            ++passed_cnt; \
    } \
    std::cout << "Loop End: Total"; \
    xtest::print_time(total); \
    std::cout << ",Avg"; \
    xtest::print_time(total / count); \
    std::cout << ", " << passed_cnt << " passed in " << count << std::endl; \
}

#define RUN(...) \
int main(int argc,char *argv[]){ \
    xtest::call(__VA_ARGS__); \
    return 0; \
}

#endif //_XTEST_RUN_H_
