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
            ss << "[ASSERT]"
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
namespace xtest{
    template <class Iter1,class Iter2>
    bool _seq_eq(Iter1 seq1b,Iter1 seq1e,Iter2 seq2b,Iter2 seq2e){
//        static_assert()
        for(;seq1b != seq1e && seq2b != seq2e;++seq1b,++seq2b){
            if(*seq1b != *seq2b){
                return false;
            }
        }
        return !(seq1b != seq1e || seq2b != seq2e);
    }
}
#define ASSERT_SEQ(seq1,seq2)\
    ASSERT(xtest::_seq_eq(std::begin((seq1)),std::end((seq1)),std::begin((seq2)),std::end((seq2))),\
           #seq1 " != " #seq2)

#endif //_XTEST_ASSERT_H_
