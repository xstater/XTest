# XTest
简单的c++测试小工具

### Example
```
///some configurations
#define XTEST_OUTPUT_FILE_FULL_PATH true

#include "XTest.hpp"

int func(){
    println("Func",1); //debug print
    return 2;
}

TEST(simple){
    ASSERT_GEQ(func(),0);//pass
}
TEST(simple2){
    ASSERT_LE(func(),0);//fail
}

RUN_TEST(simple,simple2)

```
Output
```
Func1
Func1
Assert{
        Test name:simple2
        File name:test.cpp
        File full path:D:\git\XTest\test.cpp
        Line:15
        Code:ASSERT_LE(func(),0);//fail
} => expect 'value<0' but value=2
```