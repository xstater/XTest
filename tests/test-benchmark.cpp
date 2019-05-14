#define XTEST_BENCHMARK_TIME true

#include "XTest.hpp"

BENCHMARK(test1,{
    int k = 1;
    int *p = nullptr;
    for(int i = 1;i < 10000;++i){
        ++k;
        p = new int(2);
        delete p;
    }
})

BENCHMARK(test2,{
    int k = 1;
    for(int i = 1;i < 1000000;++i){
        ++k;
    }
})

RUN(test1,test2)