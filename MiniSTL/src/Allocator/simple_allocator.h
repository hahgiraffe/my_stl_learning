/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:45:42
 * @Description: 最简单版本的Allocator，只是对::operator new 做基本封装(但是可以用jemalloc替代ptmalloc进行优化)
 */
#ifndef MINISTL_SRC_ALLOCATOR_SIMPLE_ALLOCATOR_H
#define MINISTL_SRC_ALLOCATOR_SIMPLE_ALLOCATOR_H
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <new>

namespace MINISTL{

    template <typename T>
    inline T* _allocate(ptrdiff_t size,T*){
        std::set_new_handler(0);    //set_new_hadler(handle)使得handle函数将在默认内存申请函数(operator new和operator new[])申请内存失败时被调用
        T* tmp=(T*)(::operator new((size_t) (size*sizeof(T))));//调用全局operator::new()分配一个空间，大小为size*sizeof(T),返回头指针tmp
        if(tmp==0)
        {
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }
    template <typename T>
    inline void _deallocate(T* buffer){
        ::operator delete(buffer);
    }

    template <typename T1,typename T2>
    inline void _construct(T1* p,const T2& value){//构造对象
        new(p) T1(value);
    }

    template <typename T>
    inline void _destroy(T* ptr){//析构对象
        ptr->~T();
    }

    template <typename T>
    class simple_allocator{
    public:
        //这些就是标准中规定的，一个allocator所必须具备的
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        //嵌套,用于重新绑定另一个类型,实现了对不同类型使用同一种内存分配策略的要求
        //标准中规定,对一个allocator<T>,和一个类型U,必须有allotor<T>::rebind<U>::other = allocator<U>
        //详见effective stl 10条
        template <typename U>
        struct rebind{
            typedef simple_allocator<U> other;
        };

        //size_type是要求对象的个数，返回的T*并未被构造
        pointer allocate(size_type n, const void* hint=0){
            return _allocate((difference_type)n,(pointer)0);
        }

        void deallocate(pointer p,const T& value){
            _deallocate(p);
        }
        void construct(pointer p,const T& value){
            _construct(p,value);
        }
        void destroy(pointer p,const T& value){
            _destroy(p);
        }
        pointer address(reference x){
            return (pointer)&x;
        }
        const_pointer const_address(const_reference x){
            return(const_pointer)&x;
        }

        size_type max_size() const{
            return size_type(UINT_MAX/sizeof(T));
        }

    };


}   //MINISTL

#endif //MINISTL_SRC_ALLOCATOR_SIMPLE_ALLOCATOR_H