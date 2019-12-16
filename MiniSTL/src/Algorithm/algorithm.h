/*
 * @Author: haha_giraffe
 * @Date: 2019-11-25 16:26:10
 * @Description: algorithm
 */
#ifndef MINISTL_SRC_ALGORITHM_ALGORITHM_H
#define MINISTL_SRC_ALGORITHM_ALGORITHM_H
#include "../Iterator/stl_iterator.h"
#include "../Iterator/typetraits.h"
#include <utility>

// #include "../Container/Associative/map.h" //注意依赖的问题

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
inline const T& max(const T& a, const T& b) { return a < b ? b : a; }

template <typename T, typename Compare>
inline const T& max(const T& a, const T& b, Compare comp) { return comp(a, b) ? b : a; }


//min
template <typename T>
inline const T& min(const T& a, const T& b) { return a < b ? a : b; }

template <typename T, typename Compare>
inline const T& min(const T& a, const T& b, Compare comp) { return comp(a, b) ? a : b; }


//equal
template <typename Iterator1, typename Iterator2>
bool equal(Iterator1 lbegin, Iterator1 lend, Iterator2 rbegin){
    for(Iterator1 itr = lbegin; itr != lend; ++itr){
        if(*itr != *rbegin++) return false; 
    }
    return true;
}

template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
inline bool equal(Iterator1 lbegin, Iterator1 lend, Iterator2 rbegin, BinaryPredicate bp){
    for(Iterator1 itr = lbegin; itr != lend; ++itr){
        if(!bp(*itr,*rbegin++)) return false; 
    }
    return true;
}

//iter_swap交换指针所指的元素
template <typename ForwardIterator1, typename ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b){
    typedef typename iterator_traits<ForwardIterator1>::value_type value_type;
    value_type tmp = *a;
    *a = *b;
    *b = tmp;
}

//lexicographical_compare 字典序排序比较
template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
    for( ;first1 != last1 && first2 != last2; ++first1, ++first2){
        if(*first1 < *first2){
            return true;
        }
        if(*first2 < *first1){
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
    for( ;first1 != last1 && first2 != last2; ++first1, ++first2){
        if( comp(*first1, *first2)){
            return true;
        }
        if( comp(*first2, *first1)){
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}

//mismatch,返回两个迭代器分别指向序列中第一个不匹配点
template <typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last, InputIterator2 first2){
    while(first1 != last && *first1 == *first2){
        ++first1;
        ++first2;
    }
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

template <typename InputIterator1, typename InputIterator2, typename BinaryOperation>
std::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last, InputIterator2 first2, BinaryOperation bp){
    while(first1 != last && bp(*first1, *first2)){
        ++first1;
        ++first2;
    }
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

//set相关算法
//set_union并集
template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
        }
        else if(*first2 < *first1){
            *result = *first2;
        }
        else{
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

//set_intersection交集
template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            ++first1;
        }
        else if(*first2 < *first1){
            ++first2;
        }
        else{
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return result;
}

//set_difference差集
template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first2 < *first1){
            ++first2;
        }
        else{
            ++first1;
            ++first2;
        }
    }
    return copy(first1, last1, result);
}

//set_symmetric_difference对称差集(S1 - S2) U (S2 - S1)
template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
            ++result;
        }
        else if(*first2 < *first1){
            *result = *first2;
            ++first2;
            ++result;
        }
        else{
            ++first1;
            ++first2;
        }
    }
    return copy(first2, last2, copy(first1, last1, result));
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


//upper_bound，找到适合插入value的最后一个位置
template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag){
    Distance len = 0;
    len = distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
        half = len >> 1;
        middle = first;
        advance(middle, half);  //middle指向中间位置
        if(value < *middle){
            len = half;
        }
        else{
            first = middle;
            ++first;
            len = len - half -1;
        }
    }
    return first;
}

template <typename RandomAccessIterator, typename T, typename Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag){
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;
    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (value < *middle) {
            len = half;
        }
        else{
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template <typename ForwardIterator, typename T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value){
    return __upper_bound(first, last, value, difference_type(first) , iterator_category(first));
}

}   //namespace MINISTL

#endif //MINISTL_SRC_ALGORITHM_ALGORITHM_H

