#ifndef _XTEST_ASSERT_H_
#define _XTEST_ASSERT_H_

#ifndef XTEST_OUTPUT_FULL_PATH
#define XTEST_OUTPUT_FULL_PATH false
#endif

#ifndef XTEST_ENABLE_ASSERT
#define XTEST_ENABLE_ASSERT true
#endif

#include <string>
#include <exception>
#include <sstream>

namespace xtest{
    class AssertFail : public std::exception{
    public:
        AssertFail(const char *case_name,const char *msg,const char *file_path,unsigned int line){
            std::stringstream ss;
            ss << "Assert:"
               << '\"'
               #if XTEST_OUTPUT_FULL_PATH
               << file_path
               #else
               << getFileName(file_path)
               #endif
               << "\" line "
               << line
               << " in \""
               << case_name
               << "\": "
               << msg;
            m_message = ss.str();
        }

        virtual const char *what()const noexcept{
            return m_message.c_str();
        }

    protected:
    private:
        std::string m_message;

        const char *getFileName(const char *path)const{
            auto p = path;
            ///get the end
            for(;*p != '\0';++p);
            ///find the '/' or '\'
            for(;p != path && *p != '/' && *p != '\\';--p);
            return ++p;
        }
    };

}

#if XTEST_ENABLE_ASSERT
#define ASSERT(pred,msg) if(!(pred)) throw xtest::AssertFail(__func__,msg,__FILE__,__LINE__)
#else
#define ASSERT(pred,msg)
#endif

///some useful asserts
#define ASSERT_NULL(ptr) ASSERT((ptr) != nullptr,#ptr " is a null pointer")

#endif //_XTEST_ASSERT_H_
