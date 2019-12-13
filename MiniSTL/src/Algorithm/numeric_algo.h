/*
 * @Author: haha_giraffe
 * @Date: 2019-12-13 15:37:35
 * @Description: 数值算法的实现
 */
#ifndef MINISTL_SRC_ALGORITHM_NUMERIC_ALGO_H
#define MINISTL_SRC_ALGORITHM_NUMERIC_ALGO_H
#include "../Iterator/stl_iterator.h"

namespace MINISTL{

//accumulate用于累加
template <typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init){
    for(; first != last; ++first){
        init = init + *first;
    }
    return init;
}

template <typename InputIterator, typename T, typename BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op){
    for(; first != last; ++first){
        init = binary_op(init, *first);
    }
    return init;
}

//adjacent_difference计算[first, last)中元素的差值并把其放到第二个元素中
template <typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last) return result;
    *result = *first;
    typedef typename iterator_traits<InputIterator>::value_type value_type;
    value_type value = *first;
    while(++first != last){
        value_type tmp = *first;
        *(++result) = tmp - value;
        value = tmp;
    }
    return ++result;
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op){
    if(first == last) return result;
    *result = *first;
    typedef typename iterator_traits<InputIterator>::value_type value_type;
    value_type value = *first;
    while(++first != last){
        value_type tmp = *first;
        *(++result) = binary_op(tmp, value);
        value = tmp;
    }
    return ++result;
}

//inner_product 计算[first1, last1) 和[first2, first2 + (last1 - first1))的内积
template <typename InputIterator1, typename InputIterator2, typename T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init){
    for(; first1 != last1; ++first1, ++first2){
        init = init + (*first1 * *first2);
    }
    return init;
}

template <typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 bop1, BinaryOperation2 bop2){
    for(; first1 != last1; ++first1, ++first2){
        init = bop1(init, bop2(*first1, *first2));
    }
    return init;
}

//partial_sum计算局部总和，result中元素存储开始到当前元素的总和
template <typename InputIterator, typename OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last) return result;
    *result = *first;
    typedef typename iterator_traits<InputIterator>::value_type value_type;
    value_type value = *first;
    while(++first != last){
        value = value + *first;
        *++result = value;
    }
    return ++result;
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op){
    if(first == last) return result;
    *result = *first;
    typedef typename iterator_traits<InputIterator>::value_type value_type;
    value_type value = *first;
    while(++first != last){
        value = binary_op(value, *first);
        *++result = value;
    }
    return ++result;
}


}

#endif  //MINISTL_SRC_ALGORITHM_NUMERIC_ALGO_H


