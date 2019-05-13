#define XTEST_OUTPUT_FILE_FULL_PATH true
#define XTEST_OUTPUT_LINE_CODE true

#include "XTest.hpp"

int func(){
    return 2;
}

TEST(simple){
    ASSERT_EQ(func(),0);//fail
}

RUN_TEST(simple)
