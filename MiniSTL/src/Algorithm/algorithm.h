/*
 * @Author: haha_giraffe
 * @Date: 2019-11-25 16:26:10
 * @Description: algorithm
 */
#ifndef MINISTL_SRC_ALGORITHM_ALGORITHM_H
#define MINISTL_SRC_ALGORITHM_ALGORITHM_H
#include "../Iterator/stl_iterator.h"
#include "../Iterator/typetraits.h"

namespace MINISTL{

//copy的实现

template <typename RandomAccessIterator, typename OutputIterator, typename Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator res, Distance*){
    for(Distance n = last - first; n > 0; --n, ++res, ++first){
        *res = *first;
    }
    return res;
}

template <typename Itr, typename OutputIterator>
inline OutputIterator __copy(Itr first, Itr end, OutputIterator res, input_iterator_tag){
    for( ; first != end;++res, ++first){
        *res = *first;
    }
    return res;
}

template <typename Itr, typename OutputIterator>
inline OutputIterator __copy(Itr first, Itr end, OutputIterator res, random_access_iterator_tag){
    return __copy_d(first, end, res, difference_type(first));   //这里改为difference_type
}

template <typename Itr, typename OutputIterator>
struct __copy_dispatch{
    OutputIterator operator()(Itr first, Itr end, OutputIterator res){
        return __copy(first, end, res, iterator_category(first));
    }
};

//__copy_dispatch对于Itr*的偏特化

template<typename T>
inline T* __copy_t(const T* first, const T* last, T* res, __true_type){
    memmove(res, first, sizeof(T) * (last - first) );
    return res + (last - first);
}

template<typename T>
inline T* __copy_t(const T* first, const T* last, T* res, __false_type){
    return __copy_d(first, last, res, (ptrdiff_t*)0);
}

template <typename Itr>
struct __copy_dispatch<Itr*, Itr*>{
    Itr* operator()(Itr* first, Itr* end, Itr* res){
        typedef typename _type_traits<Itr>::has_trivial_assignment_operator t;
        return __copy_t(first, end, res, t());
    }
};

//__copy_dispatch对于const Itr*的偏特化
template <typename Itr>
struct __copy_dispatch<const Itr*, Itr*>{
    Itr* operator()(const Itr* first, const Itr* end, Itr* res){
        typedef typename _type_traits<Itr>::has_trivial_assignment_operator t;
        return __copy_t(first, end, res, t());
    }
};

template <typename Itr, typename OutputIterator>
inline Itr copy(Itr begin, Itr end, OutputIterator target){
    return __copy_dispatch<Itr, OutputIterator>()(begin, end, target);
}

//copy_backward的实现，从后往前赋值（end -> begin）
template <typename Itr,typename BiItr>
inline BiItr copy_backward(Itr begin,Itr end,BiItr target){
    while (begin != end) {
        *(--target) = *(--end);
    }
    return target;
}

//fill
template <typename Itr, typename T>
inline void fill(Itr begin,Itr end,const T& value){
    for( ; begin != end; ++begin){
        *begin = value;
    }
}

//fill_n
template <typename Itr,typename Size, typename T>
inline Itr fill_n(Itr begin,Size s, T value){
    for( ;s > 0; --s, ++begin){
        *begin = value;
    }
    return begin;
}

//swap
template <typename T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

//max
template <typename T>
T max(T a, T b) { return a < b ? b : a; }

//min
template <typename T>
T min(T a, T b) { return a < b ? a : b; }

//equal
template <typename Iterator>
bool equal(Iterator lbegin, Iterator lend, Iterator rbegin){
    for(Iterator itr = lbegin; itr != lend; ++itr){
        if(*itr != *rbegin++) return false; 
    }
    return true;
}

//lower_boud,返回第一个大于等于target的一个数
//利用二分来查找左端点
template <typename ForwardIterator, typename T, typename Distance>
inline ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag){
    Distance len = 0;
    len = distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
    half = len >> 1;
        middle = first;
        advance(middle, half);  //middle指向中间位置
        if(*middle < value){
            first = middle;
            ++first;
            len = len - half -1;
        }
        else{
            len = half;
        }
    }
    return first;
}

template <typename RandomAccessIterator, typename T, typename Distance>
inline RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag){
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;
    while (len > 0) {
        half = len >> 1;
        middle = first;
        middle = first + half;
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        }
        else
            len = half;
    }
    return first;
}


//调用前一定要是有序的
template <typename ForwardIterator, typename T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value){
    return __lower_bound(first, last, value, difference_type(first) , iterator_category(first));
}



}   //namespace MINISTL

#endif //MINISTL_SRC_ALGORITHM_ALGORITHM_H

