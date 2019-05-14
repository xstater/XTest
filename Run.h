#ifndef _XTEST_RUN_H_
#define _XTEST_RUN_H_

#include <exception>

#define RUN(...) \
int main(){ \
    try{ \
        __VA_ARGS__(); \
    }catch(std::exception &e){ \
        std::cout<<e.what()<<std::endl; \
    } \
    return 0; \
}

#endif