# Benchmark

Benchmark用于测试模块的性能(运行时间和占用空间)，配合profile和memory check工具使用更佳(23333)

### Benchmark
使用`BENCHMARK_BEGIN(name)`和`BENCHMARK_END`来生成一个Benchmark<br>
```
BENCHMARK_BEGIN(test1)
    xtest::vector<int> vec;
    for(int i = 1;i < 100000;++i)
        vec.push_back(i);
BENCHMARK_END
```
使用`RUN(...)`运行Benchmark
``` 
Run(test1)
```
运行完成后
```
Benchmark:test1...[2.79976ms]
```

### 计时
* 通过定义`XTEST_BENCHMARK_MEMORY`为`true`开启计时器，默认为开启

### 内存跟踪
* 通过定义`XTEST_BENCHMARK_MEMORY`为`true`开启内存跟踪，默认关闭
* 通过定义`XTEST_BENCHMARK_TRACK_STL`为`true`跟踪计算STL容器的内存消耗，开启内存跟踪自动开启，可定义为`false`关闭
* 使用`xtest::Allocator::instance()`获得全局内存分配器的引用
* **使用内存跟踪会导致计时功能不准确**
```
#define XTEST_BENCHMARK_MEMORY true
//default -> true
//#define XTEST_BENCHMARK_TRACK_STL true 

#include <XTtest.h>
```
设定并使用`Run(test1)`
```
Benchmark:test1...[8.3974ms][768KB]
```

#### xtest::Allocator
Allocator内部使用malloc和free来分配和释放内存，并使用std::map来记录分配的内存并统计内存使用量<br>
`void *allocate(std::size_t n)`分配n个字节大小的空间，分配失败抛出`std::bad_alloc`异常<br>
`void deallocate(void *p)noexcept`释放指针p所指的空间，p可以为nullptr<br>
`void reset()noexcept`重置Allocator的内存记录
`unit::Byte getCurrentSize()const noexcept`获得当前已使用的内存大小<br>
`unit::Byte getMaxSize()const noexcept`获得最大的内存占用

#### 完整例子
```
#define XTEST_BENCHMARK_MEMORY true

#include "XTest.h"
#include "Allocator.h"

#include <vector>
#include <stack>

BENCHMARK_BEGIN(test1)
    xtest::vector<int> vec;
    for(int i = 1;i < 100000;++i)
        vec.push_back(i);
BENCHMARK_END

BENCHMARK_BEGIN(test2)
    int k = 1;
    for(int i = 1;i < 1000000;++i){
        ++k;
    }
BENCHMARK_END

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


RUN(test1,test2,test3)
```
输出
```
Benchmark:test1...[8.98907ms][768KB]
Benchmark:test2...[2.79486ms][0B]
Benchmark:test3...[308.861us][431.859KB]
```

#### links
* [Readme.md](../README.md)
* [Test & Assert](./TestAndAssert.md)
* [XUnit](https://github.com/xstater/XUnit)