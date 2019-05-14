#ifndef _XTEST_PRINT_H_
#define _XTEST_PRINT_H_

#include <iostream>

template <class ArgType>
void print(ArgType &&arg){
    std::cout << std::forward<ArgType>(arg);
}
template <class ArgType,class...ArgsType>
void print(ArgType &&arg,ArgsType&&...args){
    std::cout << std::forward<ArgType>(arg);
    print(std::forward<ArgsType>(args)...);
}

template <class ArgType>
void println(ArgType &&arg){
    std::cout << std::forward<ArgType>(arg) << std::endl;
}
template <class ArgType,class...ArgsType>
void println(ArgType &&arg,ArgsType&&...args){
    std::cout << std::forward<ArgType>(arg);
    println(std::forward<ArgsType>(args)...);
}

#endif