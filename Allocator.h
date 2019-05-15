#ifndef _XTEST_ALLOCATOR_H_
#define _XTEST_ALLOCATOR_H_

#include <stdlib.h>
#include <stdexcept>
#include <map>
#include "XUnit/Unit.hpp"

namespace xtest{
    class Allocator{
    public:
        static Allocator &instance()noexcept{
            static Allocator allocator;
            return allocator;
        }

        Allocator()
            :m_size(0.0),
             m_max_size(0.0),
             m_ptrs(){}

        void *allocate(std::size_t size){
            void *p = malloc(size);
            if(p == nullptr)
                throw std::bad_alloc();
            m_size += unit::Byte((double)size);
            m_ptrs.emplace(p,size);
            if(m_size > m_max_size)
                m_max_size = m_size;
            return p;
        }
        void deallocate(void *p) noexcept{
            if(p == nullptr)return;
            auto itr = m_ptrs.find(p);
            m_size -= unit::Byte(static_cast<double>(itr->second));
            m_ptrs.erase(itr);
            free(p);
        }

        void reset(){
            m_max_size = 0.0;
        }

        unit::Byte getCurrentSize()const noexcept{
            return m_size;
        }
        unit::Byte getMaxSize()const noexcept{
            return m_max_size;
        }
    protected:
    private:
        unit::Byte m_size;
        unit::Byte m_max_size;
        std::map<void *,std::size_t,std::less<void *>,std::allocator<std::pair<const void *, size_t>>> m_ptrs;
    };

    template <class Type>
    class TrackAllocator{
    public:
        using value_type = Type;
        using pointer = Type *;
        using const_pointer = const Type *;
        using reference = Type &;
        using const_reference = const Type &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using propagate_on_container_move_assignment = std::true_type;
        template <class U>
        struct rebind{
            typedef TrackAllocator<U> other;
        };
        using is_always_equal = std::true_type;

        Type *allocate(size_t n){
            return static_cast<Type*>(Allocator::instance().allocate(sizeof(Type) * n));
        }
        void deallocate(Type *p,size_t n){
            Allocator::instance().deallocate((void*)p);
        }
    protected:
    private:
    };
}

#endif