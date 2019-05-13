#ifndef _XTEST_H_
#define _XTEST_H_

#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

//-------Configuration----------

#if !defined(XTEST_OUTPUT_FILE_NAME)
#define XTEST_OUTPUT_FILE_NAME true
#endif

#if !defined(XTEST_OUTPUT_FILE_PATH)
#define XTEST_OUTPUT_FILE_PATH false
#endif

#if !defined(XTEST_OUTPUT_FILE_FULL_PATH)
#define XTEST_OUTPUT_FILE_FULL_PATH false
#endif

#if !defined(XTEST_OUTPUT_LINE)
#define XTEST_OUTPUT_LINE true
#endif

#if !defined(XTEST_OUTPUT_LINE_CODE)
#define XTEST_OUTPUT_LINE_CODE false
#endif

//--------Debug Output----------

//------Unit Test and Assert----

namespace xtest{
    enum class AssertType{
        equal,
        not_equal,
        less,
        greater,
        less_equal,
        greater_equal
    };


    class AssertInfo{
    public:
        AssertInfo(AssertType type,const char *file,unsigned int line)
                :m_type(type),
                 m_file_full_path(file),
                 m_line(line){}
        ~AssertInfo() = default;

        std::string getFileFullPath()const{
            return m_file_full_path;
        }
        std::string getFileName()const{
            auto itr = m_file_full_path.end() - 1;
            for(;itr != m_file_full_path.begin() && *itr != '/' && *itr != '\\';--itr);
            return std::string(++itr,m_file_full_path.end());
        }
        std::string getFilePath()const{
            auto itr = m_file_full_path.end() - 1;
            for(;itr != m_file_full_path.begin() && *itr != '/' && *itr != '\\';--itr);
            return std::string(m_file_full_path.begin(),++itr);
        }
        std::string getLineCode()const{
            std::ifstream ifile(m_file_full_path);
            if(!ifile)
                return "##Cannot open the source file##";
            char ch = ' ';
            unsigned int lineCount = 1;
            for(;!ifile.eof() && lineCount < m_line;ifile >> ch){
                if(ch == '\n')
                    ++lineCount;
            }
            for(;ch == ' ' || ch == '\t';ifile >> ch);
            std::string code;
            for(;!ifile.eof() && ch != '\n';ifile >> ch){
                code.push_back(ch);
            }
            return code;
        }
        unsigned int getLine()const{
            return m_line;
        }
    protected:
    private:
        AssertType m_type;
        std::string m_file_full_path;
        unsigned int m_line;

        std::string to_string(AssertType type){
            switch(type){
                case AssertType::equal:
                    return "==";
                case AssertType::not_equal:
                    return "!=";
                case AssertType::less:
                    return "<";
                case AssertType::greater:
                    return ">";
                case AssertType::less_equal:
                    return "<=";
                case AssertType::greater_equal:
                    return ">=";
            }
        }
    };

    template<class ValueType,class ExptValueType>
    struct AssertFail : public std::exception{
    public:
        AssertFail( const AssertInfo &info,
                    ValueType &&value,
                    ExptValueType &&expt_value){
            std::stringstream ss;
            ss << "Assert{\n";

            #if XTEST_OUTPUT_FILE_NAME
                ss << "\tFile name:" << info.getFileName() << '\n';
            #endif
            #if XTEST_OUTPUT_FILE_PATH
                ss << "\tFile path:" << info.getFilePath() << '\n';
            #endif
            #if XTEST_OUTPUT_FILE_FULL_PATH
                ss << "\tFile full path:" << info.getFileFullPath() << '\n';
            #endif

            #if XTEST_OUTPUT_LINE
                ss << "\tLine:" << info.getLine() << '\n';
            #endif

            #if XTEST_OUTPUT_LINE_CODE
                ss << "\tCode:" << info.getLineCode() << '\n';
            #endif

            ss << "} => expect " << expt_value << " but " << value << '\n';

            m_msg = ss.str();
        }
        AssertFail() = default;
        virtual const char *what()const noexcept{
            return m_msg.c_str();
        }
    private:
        std::string m_msg;
    };
}

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


#define ASSERT_EQ(value,expt_value) \
if(!(value == expt_value)) \
    throw xtest::AssertFail<decltype(value),decltype(expt_value)>( \
            {xtest::AssertType::equal,__FILE__,__LINE__}, \
            value, \
            expt_value);

#endif
