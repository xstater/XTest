#ifndef _XTEST_RUN_H_
#define _XTEST_RUN_H_

#include <exception>
#include <utility>

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

#define RUN(...) \
int main(){ \
    try{ \
        xtest::call(__VA_ARGS__); \
    }catch(std::exception &e){ \
        std::cout<<e.what()<<std::endl; \
    } \
    return 0; \
}

#endif