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

RUN(simple,simple2)
