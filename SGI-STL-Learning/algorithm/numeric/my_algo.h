/*
 * @Description:  自己写一写泛型算法
 * @Author: haha_giraffe
 * @Date: 2019-04-21 21:00:40
 */
#ifndef _MY_ALGO_H
#define _MY_ALGO_H
#include <iostream>
#include <vector>


//my_minus
template<typename T>
struct my_minus{
    T operator () (T a,T b){
        return a - b;
    }
};

//my_plus
template<typename T>
struct my_plus{
    T operator () (T a,T b){
        return a + b;
    }
};

//my_multiply
template<typename T>
struct my_multiply{
    T operator () (T a,T b){
        return a * b;
    }
};

//find
template <typename Iterator,typename T>
Iterator my_find(Iterator begin,Iterator end,const T& value){
    while(begin!=end && *begin != value){
        begin++;
    }
    return begin;
}

//accumulate version1
template <typename InputIterator,typename T>
T my_accumulate(InputIterator first,InputIterator second,T init){
    for(;first!=second;first++){
        init=init+(*first);
    }
    return init;
}
//accumulate version2
template <typename InputIterator,typename T,typename BinaryOperation>
T my_accumulate(InputIterator first,InputIterator second,T init,BinaryOperation b_op){
    for(;first!=second;first++){
        init=b_op(init,*first);
    }
    return init;
}

//adjacent_difference version1
template <typename InputIterator,typename OutputIterator>
OutputIterator my_adjacent_difference(InputIterator first,InputIterator last,OutputIterator result){
    if(first==last) return result;
    *result=*first;
    typename std::iterator_traits<InputIterator>::value_type value=*first;
    while(++first!=last){
        typename std::iterator_traits<InputIterator>::value_type tmp=*first;
        *++result=tmp-value;
        value=tmp;
    }
    return ++result;
}

//adjacent_difference version2也是加了一个仿函数
template <typename InputIterator,typename OutputIterator,typename BinaryOperation>
OutputIterator my_adjacent_difference(InputIterator first,InputIterator last,OutputIterator result,BinaryOperation binary_op){
    if(first==last) return result;
    *result=*first;
    typename std::iterator_traits<InputIterator>::value_type value=*first;
    while(++first!=last){
        typename std::iterator_traits<InputIterator>::value_type tmp=*first;
        *++result=binary_op(tmp,value);
        value=tmp;
    }
    return ++result;
}

//inner_product version1
template <typename InputIterator1,typename InputIterator2,typename T>
T my_inner_product(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,T init){
    for(;first1!=last1;first1++,first2++){
        init=init+(*first1 * *first2);
    }
    return init;
}

//inner_product version2
template<typename InputIterator1,typename InputIterator2,typename T,typename BinaryOperation1,typename BinaryOperation2>
T my_inner_product(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,T init,BinaryOperation1 bo1,BinaryOperation2 bo2){
    for(;first1!=last1;first1++,first2++){
        init=bo1(init,bo2(*first1,*first2));
    }
    return init;
}

//partial_sum实现累加，和my_adjacent_difference相似

//power,注意这里的复杂度明显降低
template <typename T,typename Integer>
T my_power(T x,Integer n){
    return __my_power(x,n,my_multiply<T> ());
}
template <typename T,typename Integer,typename Operation >
T __my_power(T x,Integer n,Operation op){
    if(n==0){
        return x;
    }
    else{
        while( (n&1)==0){
            n>>=1;
            x=op(x,x);
        }
        T result=x;
        n>>=1;
        while(n!=0){
            x=op(x,x);
            if((n&1)!=0){
                result=op(result,x);
            }
            n>>=1;
        }
        return result;
    }
}
#endif