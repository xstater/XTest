#define XTEST_OUTPUT_FILE_FULL_PATH true
#define XTEST_OUTPUT_LINE_CODE true

#include "XTest.hpp"

int func(){
    return 2;
}

TEST(simple){
    ASSERT_GEQ(func(),0);//pass
}
TEST(simple2){
    ASSERT_LE(func(),0);//fail
}

RUN_TEST(simple,simple2)
