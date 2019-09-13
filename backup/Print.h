#ifndef _XTEST_PRINT_H_
#define _XTEST_PRINT_H_

#include <iostream>
#include <sstream>

namespace xtest{
    class iobase{
    public:
        template <class ArgType>
        void print(ArgType &&arg){
            m_ss << std::forward<ArgType>(arg);
        }
        template <class ArgType,class...ArgsType>
        void print(ArgType &&arg,ArgsType&&...args){
            m_ss << std::forward<ArgType>(arg);
            print(std::forward<ArgsType>(args)...);
        }

        void println(){
            m_ss << std::endl;
        }
        template <class ArgType>
        void println(ArgType &&arg){
            m_ss << std::forward<ArgType>(arg) << std::endl;
        }
        template <class ArgType,class...ArgsType>
        void println(ArgType &&arg,ArgsType&&...args){
            m_ss << std::forward<ArgType>(arg);
            println(std::forward<ArgsType>(args)...);
        }
        
        void toConsole()const noexcept{
            std::cout << m_ss.str();
        }
        
        std::stringstream &getss(){
            return m_ss;
        }
    protected:
        std::stringstream m_ss;
    private:
    };
    class Checker : public iobase{
    public:
    protected:
    private:
    };
    class Output : public iobase{
    public:
        
    protected:
    private:
    };
}

#endif
