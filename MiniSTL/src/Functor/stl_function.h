/*
 * @Author: haha_giraffe
 * @Date: 2019-12-02 15:51:05
 * @Description: file content
 */
#ifndef MINISTL_SRC_FUNCTOR_STL_FUNCTION_H
#define MINISTL_SRC_FUNCTOR_STL_FUNCTION_H
#include <stdio.h>

namespace MINISTL{

//一元操作
template <typename Arg, typename Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};

//二元操作
template <typename Arg1, typename Arg2, typename Result>
struct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

//equal_to && not_equal_to
template <typename T>
struct equal_to : public binary_function<T, T, bool>{
    bool operator() (const T& x, const T& y) { 
        // printf("123121313\n");
        return x == y; 
    }
};

template <typename T>
struct not_equal_to : public binary_function<T, T, bool>{
    bool operator() (const T& x, const T& y) { return x != y; }
};

//greater
template <typename T>
struct greater : public binary_function<T, T, bool>{
    bool operator () (const T& x, const T& y) const { return x > y; }
};

//less
template <typename T>
struct less : public binary_function<T, T, bool>{
    bool operator () (const T& x, const T& y) const { return x < y; }
};

//identity，直接返回
template <typename T> 
struct identity : public unary_function<T, T> {
    const T& operator()(const T& x) const {
        return x;
    }
};

//select1st select2nd 注意要声明为const，因为调用时候的函数也是const
template <typename Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type>{
    const typename Pair::first_type& operator()(const Pair& x) const{
        return x.first;
    }
};

//minus
template <typename T>
struct minus : public binary_function<T, T, T>{
    T operator()(const T& x, const T& y) const { return x - y; }
};

//plus
template <typename T>
struct plus : public binary_function<T, T, T>{
    T operator()(const T& x, const T& y) const { return x + y; }
};

//bind2nd



}   //namespace MINISTL

#endif //MINISTL_SRC_FUNCTOR_STL_FUNCTION_H