#ifndef _XTEST_BENCHMARK_H_
#define _XTEST_BENCHMARK_H_

///------Configurations-------
#if !defined(XTEST_BENCHMARK_TIME)
#define XTEST_BENCHMARK_TIME true
#endif

#if !defined(XTEST_BENCHMARK_MEMORY)
#define XTEST_BENCHMARK_MEMORY false
#endif

#if !defined(XTEST_BENCHMARK_TRACK_STL)
#if XTEST_BENCHMARK_MEMORY
#define XTEST_BENCHMARK_TRACK_STL true
#else
#define XTEST_BENCHMARK_TRACK_STL false
#endif
#endif

///------Benchmark------------

#include <chrono>
#include <iostream>
#include "Allocator.h"
#include "XUnit/Unit.hpp"

namespace xtest{
    ///choose a suitable unit and print
    void print_time(const std::chrono::duration<double> &diff){
        using hours = std::chrono::duration<double,std::ratio<3600>>;
        using minutes = std::chrono::duration<double,std::ratio<60>>;
        using seconds = std::chrono::duration<double,std::ratio<1>>;
        using milliseconds = std::chrono::duration<double,std::milli>;
        using microseconds = std::chrono::duration<double,std::micro>;

        std::cout << '[';

        if(diff > hours(1)){
            std::cout
                << hours(diff).count()
                << "h";
        }else if(diff > minutes(1)){
            std::cout
                << minutes(diff).count()
                << "m";
        }else if(diff > seconds(1)){
            std::cout
                << seconds(diff).count()
                << "s";
        }else if(diff > milliseconds(1)){
            std::cout
                << milliseconds(diff).count()
                << "ms";
        }else if(diff > microseconds(1)){
            std::cout
                << microseconds(diff).count()
                << "us";
        }
        std::cout << ']';
    }
    void __print_time(const std::chrono::duration<double> &diff){
        #if XTEST_BENCHMARK_TIME
            print_time(diff);
        #endif
    }
    void print_size(const unit::Byte &bytes){
        std::cout << '[';

        if(bytes > unit::GB(1)){
            std::cout << unit::unit_cast<unit::GB>(bytes).value() << "GB";
        }else if(bytes > unit::MB(1)){
            std::cout << unit::unit_cast<unit::MB>(bytes).value() << "MB";
        }else if(bytes > unit::KB(1)){
            std::cout << unit::unit_cast<unit::KB>(bytes).value() << "KB";
        }else{
            std::cout << bytes.value() << "B";
        }

        std::cout << ']';
    }
    void __print_size(const unit::Byte &bytes){
#if XTEST_BENCHMARK_MEMORY
        print_size(bytes);
#endif
    }
}



#define BENCHMARK_BEGIN(name) \
void name() { \
    std::cout << "Benchmark:" << __func__ << "..."; \
    xtest::Allocator::instance().reset();\
    auto __start__ = std::chrono::steady_clock::now();

#define BENCHMARK_END \
    auto __end__ = std::chrono::steady_clock::now(); \
    xtest::__print_time(__end__ - __start__); \
    xtest::__print_size(xtest::Allocator::instance().getMaxSize()); \
    std::cout << std::endl; \
}


#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

#if XTEST_BENCHMARK_TRACK_STL

namespace xtest{
    template <class Type>
    using vector = std::vector<Type,TrackAllocator<Type>>;

    template <class Type>
    using deque = std::deque<Type,TrackAllocator<Type>>;

    template <class Type>
    using list = std::list<Type,TrackAllocator<Type>>;

    template <class Type>
    using forward_list = std::forward_list<Type,TrackAllocator<Type>>;

    template <class Key,class Compare = std::less<Key>>
    using set = std::set<Key,Compare,TrackAllocator<Key>>;

    template <class Key,class Compare = std::less<Key>>
    using multiset = std::multiset<Key,Compare,TrackAllocator<Key>>;

    template <class Key,class T,class Compare = std::less<Key>>
    using map = std::map<Key,T,Compare,TrackAllocator<std::pair<const Key,T>>>;

    template <class Key,class T,class Compare = std::less<Key>>
    using multimap = std::multimap<Key,T,Compare,TrackAllocator<std::pair<const Key,T>>>;

    template <class Key,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>>
    using unordered_set = std::unordered_set<Key,Hash,KeyEqual,TrackAllocator<Key>>;

    template <class Key,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>>
    using unordered_multiset = std::unordered_multiset<Key,Hash,KeyEqual,TrackAllocator<Key>>;

    template <class Key,class T,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>>
    using unordered_map = std::unordered_map<Key,T,Hash,KeyEqual,TrackAllocator<std::pair<const Key,T>>>;

    template <class Key,class T,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>>
    using unordered_multimap = std::unordered_multimap<Key,T,Hash,KeyEqual,TrackAllocator<std::pair<const Key,T>>>;

    template <class T,class Container = deque<T>>
    using stack = std::stack<T,Container>;

    template <class T,class Container = deque<T>>
    using queue = std::queue<T,Container>;

    template <class T,class Container = deque<T>,class Compare = std::less<typename Container::value_type>>
    using priority_queue = std::priority_queue<T,Container,Compare>;
}

#else

///use std::allocator
namespace xtest{
    template <class Type,class Allocator = std::allocator<Type>>
    using vector = std::vector<Type,Allocator>;

    template <class Type,class Allocator = std::allocator<Type>>
    using deque = std::deque<Type,Allocator>;

    template <class Type,class Allocator = std::allocator<Type>>
    using list = std::list<Type,Allocator>;

    template <class Type,class Allocator = std::allocator<Type>>
    using forward_list = std::forward_list<Type,Allocator>;

    template <class Key,class Compare = std::less<Key>,class Allocator = std::allocator<Key>>
    using set = std::set<Key,Compare,Allocator>;

    template <class Key,class Compare = std::less<Key>,class Allocator = std::allocator<Key>>
    using multiset = std::multiset<Key,Compare,Allocator>;

    template <class Key,class T,class Compare = std::less<Key>,class Allocator = std::allocator<std::pair<const Key,T>>>
    using map = std::map<Key,T,Compare,Allocator>;

    template <class Key,class T,class Compare = std::less<Key>,class Allocator = std::allocator<std::pair<const Key,T>>>
    using multimap = std::multimap<Key,T,Compare,Allocator>;

    template <class Key,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>,class Allocator = std::allocator<Key>>
    using unordered_set = std::unordered_set<Key,Hash,KeyEqual,Allocator>;

    template <class Key,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>,class Allocator = std::allocator<Key>>
    using unordered_multiset = std::unordered_multiset<Key,Hash,KeyEqual,Allocator>;

    template <class Key,class T,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>,class Allocator = std::allocator<std::pair<const Key,T>>>
    using unordered_map = std::unordered_map<Key,T,Hash,KeyEqual,Allocator>;

    template <class Key,class T,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>,class Allocator = std::allocator<std::pair<const Key,T>>>
    using unordered_multimap = std::unordered_multimap<Key,T,Hash,KeyEqual,Allocator>;

    template <class T,class Container = std::deque<T,std::allocator<T>>>
    using stack = std::stack<T,Container>;

    template <class T,class Container = std::deque<T,std::allocator<T>>>
    using queue = std::queue<T,Container>;

    template <class T,class Container = std::deque<T,std::allocator<T>>,class Compare = std::less<typename Container::value_type>>
    using priority_queue = std::priority_queue<T,Container,Compare>;
}

#endif

#endif//_XTEST_BENCHMARK_H_