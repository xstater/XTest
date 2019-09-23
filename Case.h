#ifndef _XTEST_CASE_H_
#define _XTEST_CASE_H_

#include <iostream>
#include <chrono>
#include "Utility.h"
#include "Result.h"

#define CASE_BEGIN(name) \
xtest::Result name(){ \
    std::cout << #name << "..." << std::endl; \
    auto __start_time = std::chrono::steady_clock::now(); \
    try{

#define CASE_END \
    }catch(std::exception &e){ \
        auto __end_time = std::chrono::steady_clock::now(); \
        auto __time = __end_time - __start_time; \
        std::cout << __func__ << "...";\
        xtest::print_time(__time); \
        std::cout << "Failed" << std::endl; \
        std::cout << e.what() << std::endl << std::endl; \
        return xtest::Result{false,__time}; \
    } \
    auto __end_time = std::chrono::steady_clock::now(); \
    auto __time = __end_time - __start_time; \
    std::cout << __func__ << "..."; \
    xtest::print_time(__time); \
    std::cout << "Pass" << std::endl << std::endl; \
    return xtest::Result{true,__time}; \
}

#endif //_XTEST_CASE_H_