# XTest
简单的c++测试小工具

### documents
* [Test & Assert](./docs/TestAndAssert.md)
* [Benchmark](./docs/Benchmark.md)

### Test Case and Assert
```
///some configurations
#define XTEST_OUTPUT_FILE_FULL_PATH true

#include "XTest.hpp"

int func(){
    //println("Func",1); //debug print
    return 2;
}

TEST_BEGIN(simple1)
    ASSERT_GEQ(func(),0);//pass
    //ASSERT_LE(func(),0);//fail
TEST_END
TEST_BEGIN(simple2)
    ASSERT_LE(func(),0);//fail
TEST_END

RUN(simple1,simple2)
```
Output
```
Test case:simple1...PASS
Test case:simple2...Assert{
        Test name:simple2
        File name:test-assert.cpp
        File full path:D:\git\XTest\tests\test-assert.cpp
        Line:16
        Code:ASSERT_LE(func(),0);//fail
} => expect 'value<0' but value=2

```

### Benchmark
```
#define XTEST_BENCHMARK_MEMORY true
#define XTEST_BENCHMARK_TRACK_STL true

#include "XTest.hpp"
#include "Allocator.h"

#include <vector>

BENCHMARK_BEGIN(test1)
    auto &allocator = xtest::Allocator::instance();
    xtest::vector<int> vec;//use vector<T> in namespace xtest to track memory
    vec.push_back(12);
    for(int i = 1; i <= 1000000;i++){
        vec.push_back(i);
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

RUN(test1,test2)
```
Output
```
Benchmark:test1...[146.191ms][6MB]
Benchmark:test2...[2.80769ms][0B]
```