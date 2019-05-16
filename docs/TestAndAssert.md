# Test & Assert

Test & Assert 用于测试模块的正确性

### Assert
所有Assert：
* `ASSERT_EQ(value,expt_value)` 期望`value==expt_value`
* `ASSERT_NEQ(value,expt_value)`期望`value!=expt_value`
* `ASSERT_GE(value,expt_value)` 期望`value>expt_value`
* `ASSERT_GEQ(value,expt_value)`期望`value>=expt_value`
* `ASSERT_LE(value,expt_value)` 期望`value<expt_value`
* `ASSERT_LEQ(value,expt_value)`期望`value<=expt_value`

若满足条件则Assert通过<br>
否则不通过，停止TestCase并输出Assert的信息


### Test Case
使用`TEST_BEGIN(name)`和`TEST_END`来生成一个TestCase<br>
```
TEST_BEGIN(fib)
    //1 1 2 3 5
    ASSERT_EQ(fib(5),5);//pass
TEST_END
```
使用`RUN(...)`来运行TestCase <br>
```
RUN(fib)
```
当TestCase通过时会输出`Test case:fib...PASS`否则就会输出对应的Assert错误信息

### 配置宏
定义以下宏可以调整Assert输出的内容<br>
格式为：`名字 = 默认值` <br>
* `XTEST_OUTPUT_FILE_NAME = true` <br>
    输出文件名
* `XTEST_OUTPUT_FILE_PATH = false` <br>
    输出文件所在目录
* `XTEST_OUTPUT_FILE_FULL_PATH = false` <br>
    输出文件完整路径
* `XTEST_OUTPUT_LINE = true` <br>
    输出行号
* `XTEST_OUTPUT_LINE_CODE = true` <br>
    输出Assert所在行的内容
* `XTEST_OUTPUT_TEST_NAME = true` <br>
    输出TestCase的名字
```
#define XTEST_OUTPUT_FILE_FULL_PATH true

#include <XTest.h>
```


#### links
* [Readme.md](../README.md)
* [Benchmark](./Benchmark.md)