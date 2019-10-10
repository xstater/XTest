#ifndef _XTEST_TIMER_H_
#define _XTEST_TIMER_H_

#include "Utility.h"

namespace xtest{
    class Timer{
    public:
        Timer(const char *name)
            :m_name(name),
            m_start(std::chrono::steady_clock::now()){}
        ~Timer(){
            auto end = std::chrono::steady_clock::now();
            std::cout << "[Timer]" << m_name << ' ';
            print_time(end - m_start);
            std::cout << std::endl;
        }
    protected:
    private:
        const char *m_name;
        decltype(std::chrono::steady_clock::now()) m_start;
    };
}

#endif //_XTEST_TIMER_H_