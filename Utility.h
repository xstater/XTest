#ifndef _XTEST_UTILITY_H_
#define _XTEST_UTILITY_H_

#include <chrono>
#include <iostream>

namespace xtest{
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
}

#endif //_XTEST_UTILITY_H_