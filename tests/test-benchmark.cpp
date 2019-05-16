#define XTEST_BENCHMARK_MEMORY true

#include "XTest.h"
#include "Allocator.h"

#include <vector>
#include <stack>

BENCHMARK_BEGIN(test3)
    auto &allocator = xtest::Allocator::instance();
    xtest::vector<int> vec;//use vector<T> in namespace xtest to track memory
    vec.push_back(12);
    for(int i = 1; i <= 100;i++){
        vec.push_back(i);
    }
    xtest::stack<int> stk;
    for(int i = 1; i <= 10000;++i){
        stk.push(i);
    }
    int *p = (int*)allocator.allocate(sizeof(int)*100000);
    allocator.deallocate(p);
BENCHMARK_END

BENCHMARK_BEGIN(test2)
    int k = 1;
    for(int i = 1;i < 1000000;++i){
        ++k;
    }
BENCHMARK_END

BENCHMARK_BEGIN(test1)
    xtest::vector<int> vec;
    for(int i = 1;i < 100000;++i)
        vec.push_back(i);
BENCHMARK_END

RUN(test1,test2,test3)