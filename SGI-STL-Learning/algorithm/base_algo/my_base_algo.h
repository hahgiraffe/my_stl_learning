/*
 * @Description:  基础算法的部分实现
 * @Author: haha_giraffe
 * @Date: 2019-04-23 19:18:51
 */
#ifndef MY_BASE_ALGO_H
#define MY_BASE_ALGO_H
#include <vector>
#include <iostream>
#include <string>

//show
template <typename InputIterator>
void show(InputIterator first,InputIterator last){
    for(;first!=last;first++){
        std::cout<<*first<<" ";
    }
    std::cout<<std::endl;
    return;
}


//equal version1，判断两个容器中元素是否相同,如果容器1中的元素多于容器2中的元素，则会出问题
template <typename InputIterator1,typename InputIterator2>
bool my_equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2){
    //如果要求两个容器元素相同，则需要加上一个if判断
    for(;first1!=last1;first1++,first2++){
        if(*first1 != *first2 ){
            return false;
        }
    }
    return true;
}
//equal version2
template <typename InputIterator1,typename InputIterator2,typename BinaryPredicate>
bool my_equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,BinaryPredicate bop){
    for(;first1!=last1;first1++,first2++){
        if(!bop(*first1,*first2) ){
            return false;
        }
    }
    return true;
}

//fill
template <typename InputIterator,typename T>
void my_fill(InputIterator first,InputIterator last,const T& value){
    for(;first!=last;first++){
        *first=value;
    }
}

//fill_in,如果n大于容器的大小，则会出问题，可以用fill_in(inserter(iv,iv.begin()),5,7);传入的是有插入而非赋写的迭代器
template <typename OutputIterator,typename Size,typename T>
OutputIterator my_fill_in(OutputIterator first,Size n,const T& value){
    for(;n>0;n--,first++){
        *first=value;
    }
    return first;
}
//iter_swap交换两个迭代器所指的元素
template <typename ForwardIterator1,typename ForwardIterator2>
void my_iter_swap(ForwardIterator1 a,ForwardIterator2 b){
    typename std::iterator_traits<ForwardIterator1>::value_type tmp=*a;
    *a=*b;
    *b=tmp;
}
//比较两个字典排序码
template <typename InputIterator1,typename InputIterator2 >
bool my_lexicographical_compare(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2){
    for(;first1 != last1 && first2 != last1;first1++,first2++){
        if(*first1< *first2){
            return true;
        }
        if(*first2< *first1){
            return false;
        }
    }
    return (first1 == last1 && first2 != last2);//当第一个序列结束，第二个未结束，返回真
}

template <typename InputIterator1,typename InputIterator2,typename Compare>
bool my_lexicographical_compare(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2,Compare comp){
    for(;first1 != last1 && first2 != last1;first1++,first2++){
        if(comp(*first1,*first2)){
            return true;
        }
        if(comp(*first2,*first1)){
            return false;
        }
    }
    return (first1 == last1 && first2 != last2);
}

//min
template <typename T>
const T& my_min (const T& a,const T& b){
    return a<b? a:b;
}

template <typename T,typename Compare>
const T& my_min(const T& a,const T& b,Compare comp){
    return comp(b,a) ? b:a;
}
//max
template <typename T>
const T& my_max (const T& a,const T& b){
    return a>b? a:b;
}

template <typename T,typename Compare>
const T& my_max (const T& a,const T& b,Compare comp){
    return comp(a,b)? a:b;
}

//mismatch
template <typename InputIterator1,typename InputIterator2>
std::pair<InputIterator1,InputIterator2> my_mismatch(InputIterator1 first1,InputIterator1 last,InputIterator2 first2){
    while(first1!=last && *first1==*first2){
        first1++;
        first2++;
    }
    return std::pair<InputIterator1,InputIterator2> (first1,first2);
}

template <typename InputIterator1,typename InputIterator2,typename Compare>
std::pair<InputIterator1,InputIterator2> my_mismatch(InputIterator1 first1,InputIterator1 last,InputIterator2 first2,Compare comp){
    while(first1!=last && comp(*first1,*first2)){
        first1++;
        first2++;
    }
    return std::pair<InputIterator1,InputIterator2> (first1,first2);
}

#endif

