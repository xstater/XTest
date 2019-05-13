#define XTEST_FILE_PATH

#include "XTest.hpp"

int func(){
    return 1;
}

TEST(simple){
    ASSERT_EQ(func(),0);//fail
}

RUN_TEST(simple)
