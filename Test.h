#ifndef _XTEST_TEST_H_
#define _XTEST_TEST_H_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

///------configurations-------------

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
#define XTEST_OUTPUT_LINE_CODE true
#endif

#if !defined(XTEST_OUTPUT_TEST_NAME)
#define XTEST_OUTPUT_TEST_NAME true
#endif

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
        AssertInfo(AssertType type,const char *name,const char *file,unsigned int line)
                :m_type(type),
                 m_test_name(name),
                 m_file_full_path(file),
                 m_line(line){}
        ~AssertInfo() = default;

        std::string getTestName()const{
            return m_test_name;
        }
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
            if(!ifile.is_open())
                return "##Cannot open the source file##";
            std::string source_code;
            ifile.seekg(0,std::ios_base::end);
            auto size = ifile.tellg();
            ifile.seekg(0,std::ios_base::beg);
            source_code.resize(size);
            ifile.read(&source_code[0],size);
            unsigned int lineCount = 1;
            auto itr = source_code.begin();
            //find that line
            for(;itr != source_code.end() && lineCount < m_line;++itr){
                if(*itr == '\n'){
                    ++lineCount;
                }
            }
            //remove suffix space or table
            for(;*itr == '\t' || *itr == ' '; ++itr);
            //find the end line char
            auto itr_end = itr;
            for(;*itr_end != '\n' && itr_end != source_code.end(); ++itr_end);
            return std::string(itr,itr_end);
        }
        unsigned int getLine()const{
            return m_line;
        }
        std::string to_string()const{
            switch(m_type){
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
                default:
                    return "NON";
            }
        }
    protected:
    private:
        AssertType m_type;
        std::string m_test_name;
        std::string m_file_full_path;
        unsigned int m_line;

    };

    template<class ValueType,class ExptValueType>
    struct AssertFail : public std::exception{
    public:
        AssertFail( const AssertInfo &info,
                    ValueType &&value,
                    ExptValueType &&expt_value){
            std::stringstream ss;
            ss << "Assert{\n";

#if XTEST_OUTPUT_TEST_NAME
            ss << "\tTest name:" << info.getTestName() << '\n';
#endif

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

            ss << "} => expect \'value" << info.to_string() << expt_value << "\' but value="  << value;

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
            {xtest::AssertType::equal,__func__,__FILE__,__LINE__}, \
            value, \
            expt_value);
#define ASSERT_NEQ(value,expt_value) \
if(!(value != expt_value)) \
    throw xtest::AssertFail<decltype(value),decltype(expt_value)>( \
            {xtest::AssertType::not_equal,__func__,__FILE__,__LINE__}, \
            value, \
            expt_value);
#define ASSERT_LE(value,expt_value) \
if(!(value < expt_value)) \
    throw xtest::AssertFail<decltype(value),decltype(expt_value)>( \
            {xtest::AssertType::less,__func__,__FILE__,__LINE__}, \
            value, \
            expt_value);
#define ASSERT_LEQ(value,expt_value) \
if(!(value <= expt_value)) \
    throw xtest::AssertFail<decltype(value),decltype(expt_value)>( \
            {xtest::AssertType::less_equal,__func__,__FILE__,__LINE__}, \
            value, \
            expt_value);
#define ASSERT_GEQ(value,expt_value) \
if(!(value >= expt_value)) \
    throw xtest::AssertFail<decltype(value),decltype(expt_value)>( \
            {xtest::AssertType::greater_equal,__func__,__FILE__,__LINE__}, \
            value, \
            expt_value);

#endif