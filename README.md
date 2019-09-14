# XTest
简单的c++测试小工具

### Sample
```
///把这个宏定义为true就可以打开这个assert检查，反之可以关闭assert，默认是true
///assert检查会拖慢运行时间
#define XTEST_ENABLE_ASSERT true

#include "XTest.h"

///CASE_BEGIN和CASE_END可以定义一个case
CASE_BEGIN(case1)
    volatile int i = 0;
    volatile int j = 0;
    for(;i < 1000000; ++i){
        ///ASSERT(pred,msg)
        ///如果pred条件没有满足，就表示发生了错误，msg就会被显示出来
        ASSERT(i == j,"Error");
        ++j;
    }
CASE_END

//RUN(cases)可以运行一堆case
//REPEAT(case,count)可以重复运行case，运行count次，并且计算平均运行时间和通过率
RUN(case1,REPEAT(case1,5))

```

