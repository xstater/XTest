#ifdef NDEBUG
#define XTEST_ENABLE_ASSERT false
#else
#define XTEST_ENABLE_ASSERT true
#endif

#include <iostream>
#include "Assert.h"
#include "Case.h"
#include "Run.h"

using namespace std;

CASE_BEGIN(case1)
    volatile int i = 0;
    volatile int j = 0;
    for(;i < 1000000; ++i){
        ASSERT(i == j,"Strange Error");
        ++j;
    }
CASE_END

RUN(case1,REPEAT(case1,100))