#ifndef _XTEST_RESULT_H_
#define _XTEST_RESULT_H_

#include <chrono>

namespace xtest{
    struct Result{
        bool pass;
        std::chrono::duration<double> time;
    };
}

#endif //_XTEST_RESULT_H_