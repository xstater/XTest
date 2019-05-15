#ifndef _XTEST_BENCHMARK_H_
#define _XTEST_BENCHMARK_H_

///------Configurations-------
#if !defined(XTEST_BENCHMARK_TIME)
#define XTEST_BENCHMARK_TIME true
#endif

#if !defined(XTEST_BENCHMARK_MEMORY)
#define XTEST_BENCHMARK_MEMORY false
#endif

///------Benchmark------------

#include <chrono>
#include <iostream>
#include "XUnit/Unit.hpp"

namespace xtest{
    ///choose a suitable unit and print
    void print_time(const std::chrono::duration<double> &diff){
        using hours = std::chrono::duration<double,std::ratio<3600>>;
        using minutes = std::chrono::duration<double,std::ratio<60>>;
        using seconds = std::chrono::duration<double,std::ratio<1>>;
        using milliseconds = std::chrono::duration<double,std::milli>;
        using microseconds = std::chrono::duration<double,std::micro>;

        std::cout << '[';

        if(diff > hours(1)){
            std::cout
                << hours(diff).count()
                << "h";
        }else if(diff > minutes(1)){
            std::cout
                << minutes(diff).count()
                << "m";
        }else if(diff > seconds(1)){
            std::cout
                << seconds(diff).count()
                << "s";
        }else if(diff > milliseconds(1)){
            std::cout
                << milliseconds(diff).count()
                << "ms";
        }else if(diff > microseconds(1)){
            std::cout
                << microseconds(diff).count()
                << "us";
        }
        std::cout << ']';
    }
    void __print_time(const std::chrono::duration<double> &diff){
        #if XTEST_BENCHMARK_TIME
            print_time(diff);
        #endif
    }
    void print_size(const unit::Byte &bytes){
        std::cout << '[';

        if(bytes > unit::GB(1)){
            std::cout << unit::unit_cast<unit::GB>(bytes).value() << "GB";
        }else if(bytes > unit::MB(1)){
            std::cout << unit::unit_cast<unit::MB>(bytes).value() << "MB";
        }else if(bytes > unit::KB(1)){
            std::cout << unit::unit_cast<unit::KB>(bytes).value() << "KB";
        }else{
            std::cout << bytes.value() << "B";
        }

        std::cout << ']';
    }
    void __print_size(const unit::Byte &bytes){
#if XTEST_BENCHMARK_MEMORY
        print_size(bytes);
#endif
    }
}



#define BENCHMARK_BEGIN(name) \
void name() { \
    std::cout << "Benchmark:" << __func__ << "..."; \
    xtest::Allocator::instance().reset();\
    auto __start__ = std::chrono::steady_clock::now();

#define BENCHMARK_END \
    auto __end__ = std::chrono::steady_clock::now(); \
    xtest::print_time(__end__ - __start__); \
    xtest::print_size(xtest::Allocator::instance().getMaxSize()); \
    std::cout << std::endl; \
}

#endif//_XTEST_BENCHMARK_H_