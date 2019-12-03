#ifdef NDEBUG
#define XTEST_ENABLE_ASSERT false
#else
#define XTEST_ENABLE_ASSERT true
#endif

#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include "Assert.h"
#include "Case.h"
#include "Run.h"
#include "Info.h"

using namespace std;

CASE_BEGIN(case1)
    volatile int i = 0;
    volatile int j = 0;
    for(;i < 1000000; ++i){
        ASSERT(i == j,"Strange Error");
        ++j;
    }
CASE_END

CASE_BEGIN(multi_thread_test)
    for(int i = 1;i < 10;i++){
        std::thread t([i]()->void{
            std::this_thread::yield();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            INFOT("thread:",i);
        });
        t.detach();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
CASE_END

CASE_BEGIN(seq_test)
    vector<int> v1 = {1,2,3,3};
    list<int> l1 = {1,2,3};
    ASSERT_SEQ(v1,l1);
CASE_END

//RUN(case1,REPEAT(case1,100))
RUN(seq_test);