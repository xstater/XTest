#include <XTest.h>

TEST_BEGIN(testprint)
    xtest::Output out;
    out.println(1,'\t',true,"nmsl");
    out.toConsole();
TEST_END

RUN(testprint)
