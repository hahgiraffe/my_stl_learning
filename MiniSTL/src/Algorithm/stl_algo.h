/*
 * @Author: haha_giraffe
 * @Date: 2019-12-14 19:43:25
 * @Description: more extends algorithm
 */
#ifndef MINISTL_SRC_ALGORITHM_STL_ALGO_H
#define MINISTL_SRC_ALGORITHM_STL_ALGO_H
#include "../Iterator/stl_iterator.h"
#include "./heap_algorithm.h"
#include "./algorithm.h"

namespace MINISTL{

//adjacent_find 找到第一个相邻重复元素
template <typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
    if(first == last) return last;
    ForwardIterator next = first;
    while(++next != last){
        if(*first == *next) return first;
        first = next;
    }
    return last;
}

template <typename ForwardIterator, typename BinaryOperator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryOperator bop){
    if(first == last) return last;
    ForwardIterator next = first;
    while(++next != last){
        if(bop(*first, *next)) return first;
        first = next;
    }
    return last;
}

//count && count_if
template <typename InputIterator, typename T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(*first == value){
            ++n;
        }
    }
    return n;
}

template <typename InputIterator, typename Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(pred(*first)){
            ++n;
        }
    }
    return n;
}

//find && find_if
template <typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& value){
    while(first != last && *first != value) ++first;
    return first;
}

template <typename InputIterator, typename Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred){
    while(first != last && !pred(*first)) ++first;
    return first;
}

//find_end,在[first1, last1)覆盖区间中查找[first2,last2)最后一次出现点,如果没找到则返回last1
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag){
    //单向迭代器
    if(first2 == last2){
        return last1;
    }
    else
    {
        ForwardIterator1 result = last1;
        while(1){
            ForwardIterator1 new_result = search(first1, last1, first2, last2);
            if(new_result == last1){
                return result;
            }
            else{
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }
}

template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator1 __find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2, BidirectionalIterator2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag){
    //双向迭代器 reverse_iterator 
    // TODO
    // typedef reverse
}

template <typename ForwardIterator1, typename ForwardIterator2>
inline ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
    typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
    typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;
    return __find_end(first1, last1, first2, last2, category1(), category2());
}

//find_first_of在[first1，last1)中查找[first2, last2)的出现第一个元素
template <typename InputIterator, typename ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2){
    for(; first1 != last1; ++first1){
        for(ForwardIterator iter = first2; iter != last2; ++iter){
            if(*first1 == *iter){
                return first1;
            }
        }
    }
    return last1;
}

template <typename InputIterator, typename ForwardIterator, typename BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp){
    for(; first1 != last1; ++first1){
        for(ForwardIterator iter = first2; iter != last2; ++iter){
            if(comp(*first1, *iter)){
                return first1;
            }
        }
    }
    return last1;
}

//for_each，第三个参数为仿函数
template <typename InputIterator, typename Function>
Function for_each(InputIterator first, InputIterator last, Function f){
    for(; first != last; ++first){
        f(*first);
    }
    return f;
}

//generate && generate_n
template <typename InputIterator, typename Generator>
Generator generate(InputIterator first, InputIterator last, Generator gen){
    for(; first != last; ++first){
        *first = gen();
    }
}

template <typename OutputIterator, typename Size, typename Generator>
OutputIterator generator_n(OutputIterator first, Size n, Generator gen){
    for(; n > 0; --n, ++first){
        *first = gen();
    }
    return first;
}

//include 作用于有序空间，判断S2中是否每个元素都在S1中
template <typename InputIterator1, typename InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1){
            return false;
        }
        else if(*first1 < *first2){
            ++first1;
        }
        else{
            ++first1;
            ++first2;
        }
    }
    return first2 == last2;
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first2 , *first1)){
            return false;
        }
        else if(comp(*first1 , *first2)){
            ++first1;
        }
        else{
            ++first1;
            ++first2;
        }
    }
    return first2 == last2;
}

//max_element 最大元素
template <typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last){
    if(first == last) return first;
    ForwardIterator result = first;
    while( ++first != last){
        if(*result < *first){
            result = first;
        }
    }
    return result;
}

template <typename ForwardIterator, typename Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp){
    if(first == last) return first;
    ForwardIterator result = first;
    while( ++first != last){
        if(comp(*result , *first)){
            result = first;
        }
    }
    return result;
}

//min_element 最小元素
template <typename ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last){
    if(first == last) return first;
    ForwardIterator result = first;
    while( ++first != last){
        if(*first < *result){
            result = first;
        }
    }
    return result;
}

template <typename ForwardIterator, typename Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp){
    if(first == last) return first;
    ForwardIterator result = first;
    while( ++first != last){
        if(comp(*first , *result)){
            result = first;
        }
    }
    return result;
}

//merge 应用于有序空间
template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1){
            *result = *first2;
            ++first2;
        }
        else{
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first2 , *first1)){
            *result = *first2;
            ++first2;
        }
        else{
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

//partition 区间按照pred重新排列
template <typename BidirectionalIterator, typename Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred){
    while(true){
        while(true){
            if(first != last){
                return first;
            }
            else if(pred(*first)){
                ++first;
            }
            else{
                break;
            }
        }
        --last;
        while(true){
            if(first == last){
                return first;
            }
            else if(!pred(*last)){
                --last;
            }
            else{
                break;
            }
        }
        iter_swap(first, last);
        ++first;
    }
}

//remove && remove_copy && remove_if && remove_copy_if

template <typename InputIterator,typename OutputIterator, typename T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value){
    for( ;first != last; ++first){
        if(*first != value){
            *result = *first;
            ++result;
        }
    }
    return result;
}

template <typename InputIterator,typename OutputIterator, typename Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred){
    for( ;first != last; ++first){
        if(!pred(*first)){
            *result = *first;
            ++result;
        }
    }
    return result;
}

template <typename ForwardIterator, typename Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred){
    first = find_if(first, last, pred);
    ForwardIterator next = first;
    return first == last ? first : remove_copy_if(++next, last, first, pred);
}

template <typename ForwardIterator, typename T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value){
    first = find(first, last, value);
    ForwardIterator next = first;
    return first == last ? first : remove_copy(++next, last, first, value);
}

//replace && replace_copy && replace_if
template <typename ForwardIterator, typename T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value){
    for(; first != last; ++first){
        if(*first == old_value){
            *first = new_value;
        }
    }
}

template <typename InputIterator,typename OutputIterator, typename T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value){
    for( ;first != last; ++first, ++result){
        *result = *first == old_value ? new_value : *first;
    }
    return result;
}

template <typename ForwardIterator,typename Predicate, typename T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value){
    for( ; first != last; ++first){
        if(pred(*first)) *first = new_value;
    }
}

template <typename Iterator, typename OutputIterator, typename Predicate, typename T>
OutputIterator replace_copy_if(Iterator first, Iterator last, OutputIterator result, Predicate pred, const T& value){
    for(; first != last; ++first, ++result){
        *result = pred(*first) ? value : *first;
    }
    return result;
}

//reverse

template <typename BidirectionalIterator, typename OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result){
    while(first != last){
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

template <typename BidirectionIterator>
void __reverse(BidirectionIterator first, BidirectionIterator last, bidirectional_iterator_tag){
    while(true){
        if(first == last || first == --last){
            return;
        }
        else{
            iter_swap(first++, last);
        }
    }
}

template <typename RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    while(first < last){
        iter_swap(first++, --last);
    }
}

template <typename BidirectionIterator>
inline void reverse(BidirectionIterator first, BidirectionIterator last){
    __reverse(first, last, iterator_category(first));
}

//rotate 两个序列中元素互换
template <typename ForwardIterator, typename OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result){
    return copy(first, middle, copy(middle, last, result));
}

template <typename ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last){
    //
}

//search && search_n
template <typename ForwardIterator1, typename ForwardIterator2, typename Distance1, typename Distance2>
inline ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*){
    Distance1 d1 = 0;
    distance(first1, last1, d1);
    Distance2 d2 = 0;
    distance(first2, last2, d2);
    if(d1 < d2) return last1;
    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;
    while(current2 != last2){
        if(*current1 == *current2){
            ++current1;
            ++current2;
        }
        else{
            if(d1 == d2){
                return last1;
            }
            else{
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

template <typename ForwardIterator1, typename ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
    return __search(first1, last1, first2, last2, difference_type(first1), difference_type(first2));
}

template <typename ForwardIterator1, typename Integer, typename T>
ForwardIterator1 search_n(ForwardIterator1 first, ForwardIterator1 last, Integer count, const T& value){
    if(count <= 0) return first;
    else{
        first = find(first, last, value);
        while(first != last){
            Integer n = count - 1;
            ForwardIterator1 i = first;
            ++i;
            while(i != last && n != 0 && *i == value){
                ++i;
                --n;
            }
            if(n == 0){
                return first;
            }
            else{
                first = find(i, last, value);
            }
        }
        return first;
    }
}

//swap_ranges 交换两个区间内的元素
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
    for( ; first1 != last1; ++first1, ++first2){
        iter_swap(first1, first2);
    }
    return first2;
}

//transform
template <typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op){
    for(; first != last; ++first, ++result){
        *result = op(*first);
    }
    return result;
}

template <typename InputIterator,typename InputIterator2, typename OutputIterator, typename BinaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, InputIterator2 first2, OutputIterator result, BinaryOperation op){
    for(; first != last; ++first, ++first2, ++result){
        *result = op(*first, *first2);
    }
    return result;
}

//unique && unique_copy
template <typename InputIterator, typename ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag){
    *result *first;
    while(++first != last){
        if(*result != *first){
            *++result = *first;
        }
    }
    return ++result;
}


template <typename InputIterator, typename OutputIterator, typename T>
OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, T*){
    T value = *first;
    *result = value;
    while(++first != last){
        if(value != *first){
            value = *first;
            *++result = value;
        }
    }
    return ++result;
}

template <typename InputIterator, typename OutputIterator>
OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag){
    return __unique_copy(first, last, result, value_type(first));
}

template <typename InputIterator, typename OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last) return result;
    return __unique_copy(first, last, result, iterator_category(result));
}

template <typename ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last){
    first = adjacent_find(first, last);
    return unique_copy(first, last, first);
}

//binary_search 二分查找原始版
template <typename ForwardIterator, typename T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value){
    ForwardIterator i = lower_bound(first, last, value);
    return i != last && !(value < *i);
}

//next_permutation 下一个排列组合的序列
template <typename BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last){
    if(first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if(i == last) return false;     //只有一个元素
    i = last;
    --i;
    for(;;){
        BidirectionalIterator ii = i;
        --i;
        if(*i < *ii){
            BidirectionalIterator j = last;
            while(!(*i < *--j));    //找到第一个*j < *i
            iter_swap(i, j);        //交换i和j指针所指元素
            reverse(ii, last);      //ii到尾部reverse
            return true;
        }
        if( i == first){
            reverse(first, last);
            return false;
        }
    }
}

//prev_permutation
template <typename BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last){
    if(first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if(i == last) return false;     //只有一个元素
    i = last;
    --i;
    for(;;){
        BidirectionalIterator ii = i;
        --i;
        if(*ii < *i){
            BidirectionalIterator j = last;
            while(!(*--j < *--i));    //找到第一个*j >= *i
            iter_swap(i, j);        //交换i和j指针所指元素
            reverse(ii, last);      //ii到尾部reverse
            return true;
        }
        if( i == first){
            reverse(first, last);
            return false;
        }
    }
}

//random_shuffle 将区间内的元素次序随机重排,内部实现就是[first, last)内部随机交换
template <typename RandomAccessIterator, typename Distance>
inline void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance*){
    if(first == last) return;
    for(RandomAccessIterator i = first + 1; i != last; ++i){
        iter_swap(i, first + Distance(rand() % (i - first + 1)));
    }
}

template <typename RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last){
    __random_shuffle(first, last, difference_type(first));
}

//partial_sort 保证[first, middle)中的数递增且为最小的k个数，[middle, last)不保证顺序 （前k小的数）
template <typename RandomAccessIterator, typename T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*){
    make_heap(first, middle);
    for(RandomAccessIterator i = middle; i < last ; ++i){
        if(*i < *first){
            __pop_heap(first, middle, i, T(*i), difference_type(first));
        }
    }
    sort_heap(first, middle);
}

template <typename RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last){
    __partial_sort(first, middle, last, value_type(first));
}

//sort
//insert_sort

template <typename RandomAccessIterator, typename T>
void __unguarded_linear_insert(RandomAccessIterator last, T value){
    RandomAccessIterator next = last;
    --next;
    while(value < *next){
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}

template <typename RandomAccessIterator, typename T>
void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*){
    T value = *last;
    if(value < *first){
        copy_backward(first, last, last + 1);
        *first = value;
    }
    else{
        __unguarded_linear_insert(last, value);
    }
}

template <typename RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
    if(first == last) return;
    for(RandomAccessIterator i = first + 1; i != last; ++i){
        __linear_insert(first, i, value_type(first));
    }
}

//quick_sort(三点中值取pivot)
template <typename T>
inline const T& __median(const T& a, const T& b, const T& c){
    if(a < b){
        if(b < c){
            // a < b < c
            return b;
        }
        else if(a < c){
            // a < c <= b
            return c;
        }
        else{
            return a;
        }
    }
    else if(a < c){
        // b <= a < c
        return a;
    }
    else if(b < c){
        // b < c <= a
        return c;
    }
    else{
        return b;
    }
}

template <typename RandomAccessIterator, typename T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, T pivot){
    while(true){
        while(*first < pivot) ++first;      //first找到大于等于pivot就停下
        --last;
        while(pivot < *last) --last;        //last找到小于等于pivot就停下
        if(!(first < last)) return first;   //如果first和last指针相遇则返回
        iter_swap(first, last);
        ++first;
    }
}

const int STL_THRESHOLD = 16;
//控制最差的partition次数
template <typename Size>
inline Size __lg(Size n){
    Size k;
    for(k = 0; n > 1; n >>= 1) ++k;
    return k;
}

template <typename RandomAccessIterator, typename T>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last, T*){
    for(RandomAccessIterator i = first; i != last; ++i){
        __unguarded_linear_insert(i, T(*i));
    }
}

template <typename RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
    if(last - first > STL_THRESHOLD){
        __insertion_sort(first, first + STL_THRESHOLD);
        __unguarded_insertion_sort(first + STL_THRESHOLD, last, value_type(last));
    }
    else{
        __insertion_sort(first, last);
    }
}

template <typename RandomAccessIterator, typename T, typename Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*, Size depth_limit){
    while(last - first > STL_THRESHOLD){
        if(depth_limit == 0){
            partial_sort(first, last, last);
            return;
        }
        --depth_limit;
        RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first + (last - first)/2), *(last - 1))));
        __introsort_loop(cut, last, value_type(first), depth_limit);
        last = cut;
    }
}

template <typename RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last){
    if(first != last){
        __introsort_loop(first, last, value_type(first), __lg(last - first)*2);
        __final_insertion_sort(first, last);
    }
}

//equal_range

//inplace_merge

//n_element

//merge_sort



}   //namespace MINISTL

#endif //MINISTL_SRC_ALGORITHM_STL_ALGO_H