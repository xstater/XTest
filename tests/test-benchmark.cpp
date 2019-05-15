#define XTEST_BENCHMARK_MEMORY true

#include "XTest.hpp"
#include "Allocator.h"

#include <iostream>
#include <vector>
using namespace std;

BENCHMARK_BEGIN(test1)
    auto &allocator = xtest::Allocator::instance();
    std::vector<int,xtest::TrackAllocator<int>> vec;
    vec.push_back(12);
    for(int i = 1; i <= 1000;i++){
        vec.push_back(i);
    }
    cout << allocator.getMaxSize().value() << endl;
BENCHMARK_END

BENCHMARK_BEGIN(test2)
    cout << xtest::Allocator::instance().getCurrentSize().value() << endl;
    int k = 1;
    for(int i = 1;i < 1000000;++i){
        ++k;
    }
BENCHMARK_END

RUN(test1,test2)