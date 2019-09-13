# XTest
简单的c++测试小工具

### documents
* [Test & Assert](./docs/TestAndAssert.md)
* [Benchmark](./docs/Benchmark.md)

### Todo
* 简化assert语法
* 合并Benchmark和Testcase
* 通过宏切换Benchmark和Testcase模式
* 修改报错格式
```    "Main.cpp" line 37 in "case1":Pointer is Null```
* 修改Benchmark的时间显示格式
```
case1... 120ms
case2... 180ms
case3... 300ms

all   [==========] 600ms
case1 [==        ] 120ms
case2 [  ===     ] 180ms
case3 [     =====] 300ms
```
