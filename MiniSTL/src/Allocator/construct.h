/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:22:25
 * @Description: 初始化工作
 */
#ifndef MINI_STL_SRC_ALLOCATOR_CONSTRUCT_H
#define MINI_STL_SRC_ALLOCATOR_CONSTRUCT_H
#include <new>
#include "../Iterator/typetraits.h"
namespace MINISTL{

//constructor就是类似placement new的作用
template <typename T1,typename T2>
inline void construct(T1* p, T2 value){
    new (p) T1(value);
}

//第一个版本destroy直接调用析构函数
template <typename T>
inline void destroy(T* p){
    p->~T();
}

//第二个版本destroy通过迭代器区间,这里通过type_traits得到Iterator的类型
template <typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last){
    using is_POD_type = typename _type_traits<ForwardIterator>::is_POD_type;
    _destroy_aux(first, last, is_POD_type());
}

//如果有non-trivial destructor,则可以直接遍历两个迭代器调用析构函数
template <class ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
    for (; first != last; ++first)
        destroy(&*first); 
}

// 存在trivial destructor,则忽视即可
template <class ForwardIterator> 
inline void _destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

//destroy的偏特化版本
inline void destroy(char*, char*){ }
inline void destroy(wchar_t*, wchar_t*){ }

}   //MINISTL

#endif //MINI_STL_SRC_ALLOCATOR_CONSTRUCT_H