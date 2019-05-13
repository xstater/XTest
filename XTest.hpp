#ifndef _XTEST_H_
#define _XTEST_H_

#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

//----------Debug Output--------

//------Unit Test and Assert----

#define TEST(name) void name()

#define RUN_TEST(...) \
int main(){ \
    try{ \
        __VA_ARGS__(); \
    }catch(std::exception &e){ \
        std::cout<<e.what()<<std::endl; \
    } \
    return 0; \
}

namespace xtest{
    template<class ValueType,class ExptValueType>
    struct AssertingFail : public std::exception{
    public:
        AssertingFail(const char *assert_type,
                      const char *file,
                      unsigned int line,
                      ValueType &&value,
                      ExptValueType &&expt_value){
            std::stringstream ss;
            ss << "Assert["
               << file
               << ","
               << line
               << "]:expect "
               << expt_value
               << " but "
               << value;
            m_msg = ss.str();
        }
        AssertingFail() = default;
        virtual const char *what()const noexcept{
            return m_msg.c_str();
        }
    private:
        std::string m_msg;
    };
}

#define ASSERT_EQ(value,expt_value) \
if(!(value == expt_value)) \
    throw xtest::AssertingFail<decltype(value),decltype(expt_value)>("==",__FILE__,__LINE__,value,expt_value);

#endif
