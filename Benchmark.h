#ifndef _XTEST_BENCHMARK_H_
#define _XTEST_BENCHMARK_H_

#include <chrono>
#include <iostream>

///------Configurations-------
#if !defined(XTEST_BENCHMARK_TIME)
#define XTEST_BENCHMARK_TIME true
#endif

#if !defined(XTEST_BENCHMARK_SPACE)
#define XTEST_BENCHMARK_SPACE false
#endif

///------Benchmark------------

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
}



#define BENCHMARK(name,code) \
void name(){ \
    std::cout << "Benchmark:" << __func__ << "..."; \
    auto start = std::chrono::steady_clock::now(); \
    code \
    auto end = std::chrono::steady_clock::now(); \
    xtest::__print_time(end - start); \
    std::cout << std::endl; \
}

#endif//_XTEST_BENCHMARK_H_