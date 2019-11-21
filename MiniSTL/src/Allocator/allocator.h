/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:19:37
 * @Description: 二级内存分配器
 */
#ifndef MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H
#define MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H
#include "alloc.h"
#include "construct.h"
#include <iostream>

namespace MINISTL{

//根据Alloc默认参数来确定分配器级数
//注意allocator中的所有成员函数都要是static
template <typename T,typename Alloc = __default_alloc>
class allocator{
public:
    //这些就是标准中规定的，一个allocator所必须具备的
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
    template <typename U>
    struct rebind{
        typedef allocator<U> other;
    };

public:
    //allocate
    static T* allocate(size_t n){
        return 0 == n ? 0 : (T*) Alloc::allocate(n * sizeof(T));
    }
    static T* allocate(void){
        return (T*) Alloc::allocate(sizeof(T));
    }

    //deallocate
    static void deallocate(T* p, size_t n){
        if(n != 0){
            Alloc::deallocate(p,n * sizeof(T));
        }
    }
    static void deallocate(T* p){
        Alloc::deallocate(p, sizeof(T));
    }
    
    //construct placement new 完成
    static void construct(T *ptr){
        new (ptr) T();
    }
    static void construct(T *ptr, const T &value){
        new (ptr) T(value);
    }
    
    //destroy
    static void destroy(T *ptr){
        // std::cout<<"111"<<std::endl;
        ptr->~T();
    }
    static void destroy(T *first, T *last){
        // std::cout<<"222"<<std::endl;
        for(;first!=last;first++){
            first->~T();
        }
    }
};

}   //MINISTL

#endif //MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H