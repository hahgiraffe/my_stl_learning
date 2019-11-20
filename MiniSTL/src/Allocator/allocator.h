/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:19:37
 * @Description: 二级内存分配器
 */
#ifndef MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H
#define MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H
#include "alloc.h"
#include "construct.h"

namespace MINISTL{

//根据Alloc默认参数来确定分配器级数
//注意allocator中的所有成员函数都要是static
template <typename T,typename Alloc = __default_alloc>
class allocator{
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
    
    //construct
    static void construct(T *ptr){
        new (ptr) T();
    }
    static void construct(T *ptr, const T &value){
        new (ptr) T(value);
    }
    
    //destroy
    static void destroy(T *ptr){
        ptr->~T();
    }
    static void destroy(T *first, T *last){
        for(;first!=last;first++){
            first->~T();
        }
    }
};

}   //MINISTL

#endif //MINI_STL_SRC_ALLOCATOR_ALLOCATOR_H