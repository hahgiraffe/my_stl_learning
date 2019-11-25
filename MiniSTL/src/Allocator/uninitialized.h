/*
 * @Author: haha_giraffe
 * @Date: 2019-11-21 15:25:21
 * @Description: stl_uninitialized
 */
#ifndef MINISTL_SRC_ALLOCATOR_UNINITIALIZED
#define MINISTL_SRC_ALLOCATOR_UNINITIALIZED
#include "./construct.h"
#include "../Iterator/typetraits.h"
#include "../Iterator/stl_iterator.h"
#include "../Algorithm/algorithm.h"

namespace MINISTL{

//uninitialized_copy,将[first,last)移动到[res,res+last-first)
template< typename InputIterator, typename ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator res, __true_type){
    return copy(first, last, res);
}

template< typename InputIterator, typename ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator res, __false_type){
    ForwardIterator cur;
    for(; first != last; ++first, ++cur){
        construct(&*cur, *first);
    }
    return cur;
}

template< typename InputIterator, typename ForwardIterator,typename T>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator res, T* value){
    typedef typename _type_traits<T>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, res, is_POD());
}

template< typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator res){
    return __uninitialized_copy(first, last, res, value_type(first));
}




//uninitialized_fill，将[first,last)填充value
//针对char*、wchar_t*存在特化高效版本 memmove直接移动内存
template< typename ForwardIterator, typename T>
void __uninitialized_fill__aux(ForwardIterator first, ForwardIterator last, const T& value, __true_type){
    fill(first, last, value);
}

template< typename ForwardIterator, typename T>
void __uninitialized_fill__aux(ForwardIterator first, ForwardIterator last, const T& value, __false_type){
    ForwardIterator cur = first;
    for(; cur != last; ++cur){
        construct(&*cur, value);
    }
}

template< typename ForwardIterator, typename T, typename T1>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value, T1*){
    typedef typename _type_traits<T1>::is_POD_type is_POD;
    __uninitialized_fill__aux(first, last, value, is_POD());
}

template< typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value){
    __uninitialized_fill(first, last, value, value_type(first));
}


//uninitialized_copy
char *uninitialized_copy(const char *first, const char *last, char *result) {
    memmove(result, first, last - first);
    return result + (last - first);
}

wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result) {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}


//uninitialized_fill_n，将[first,first+n)填充value
template< typename ForwardIterator,typename Size, typename T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __true_type){
    return fill_n(first, n, value);
}

template< typename ForwardIterator,typename Size, typename T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __false_type){
    ForwardIterator cur = first;
    for(;n>0;--n,++cur){
        construct(&*cur,value);
    }
    return cur;
}

template< typename ForwardIterator,typename Size, typename T, typename T1>
ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& value,T1*){
    typedef typename _type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, value, is_POD());
}

template< typename ForwardIterator,typename Size, typename T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& value){
    return __uninitialized_fill_n(first, n, value, value_type(first));
}

}

#endif //MINISTL_SRC_ALLOCATOR_UNINITIALIZED