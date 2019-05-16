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
