/*
 * @Description:  简单算法实现
 * @Author: haha_giraffe
 * @Date: 2019-04-24 19:12:10
 */
#ifndef MY_ALGO_H
#define MY_ALGO_H
#include <iterator>

struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag:public input_iterator_tag { };
struct bidirectional_iterator_tag:public forward_iterator_tag { };
struct random_access_iterator_tag:public bidirectional_iterator_tag { };



//adjacent_find找到满足条件的相邻元素,这个判断相等
template <typename ForwardIterator>
ForwardIterator my_adjacent_find(ForwardIterator first,ForwardIterator last){
    if(first==last) return last;
    ForwardIterator next=first;
    while(++next != last){
        if(*first==*next) return first;
        first=next;
    }
    return last;
}

template <typename ForwardIterator,typename BinaryOperation>
ForwardIterator my_adjacent_find(ForwardIterator first,ForwardIterator last,BinaryOperation bop){
    if(first==last) return last;
    ForwardIterator next=first;
    while(++next != last){
        if(bop(*first,*next)) return first;
        first=next;
    }
    return last;
}

//count,在[first,last)区间中对指定value进行计数
template <typename InputIterator, typename T>
typename  std::iterator_traits<InputIterator>::difference_type
my_count(InputIterator first,InputIterator last,const T& value){
    typename  std::iterator_traits<InputIterator>::difference_type tmp=0;
    for(;first!=last;first++){
        if(*first==value){
            tmp++;
        }
    }
    return tmp;
}

template <typename InputIterator, typename Predicate>
typename  std::iterator_traits<InputIterator>::difference_type
my_count_if(InputIterator first,InputIterator last,Predicate pred){
    typename  std::iterator_traits<InputIterator>::difference_type tmp=0;
    for(;first!=last;first++){
        if(pred(*first)){
            tmp++;
        }
    }
    return tmp;
}

//find找到第一个匹配条件的，返回迭代器
template <typename InputIterator,typename T>
InputIterator my_find(InputIterator first,InputIterator last,const T& value){
    while(first!=last && *first!=value){
        ++first;
    }
    return first;
}

template <typename InputIterator,typename Predicate>
InputIterator my_find_if(InputIterator first,InputIterator last,Predicate pred){
    while(first!=last && !pred(*first)){
        ++first;
    }
    return first;
}

//find_end 在[first1,last1)覆盖区间中，查找[first2,last2)最后一次出现点，如果不存在完全覆盖则返回last1
template <typename ForwardIterator1 ,typename ForwardIterator2>
ForwardIterator1 my_find_end(ForwardIterator1 first1,ForwardIterator1 last1,ForwardIterator2 first2,ForwardIterator2 last2){
    typedef typename std::iterator_traits<ForwardIterator1>::iterator_category category1;
    typedef typename std::iterator_traits<ForwardIterator2>::iterator_category category2;
    return __my_find_end(first1,last1,first2,last2,category1(),category2());//这里有个技巧，用函数调用传递迭代器类型的临时对象，通过编译器自动推导自动对应某个函数
}
//ForwardIterator版本
template <typename ForwardIterator1 ,typename ForwardIterator2>
ForwardIterator1 __my_find_end(ForwardIterator1 first1,ForwardIterator1 last1,ForwardIterator2 first2,ForwardIterator2 last2,
                                forward_iterator_tag,forward_iterator_tag)
{
    if(first2==last2){
        return last1;
    }
    else{
        ForwardIterator1 result=last1;
        while(1){
            ForwardIterator1 new_result = my_search(first1,last1,first2,last2);//查找首次出现点
            if(new_result==last1){
                return result;
            }
            else{
                result=new_result;
                first1=new_result;
                ++first1;
            }
        }
        return result;
    }
}
//bidirectional_iterator版本，可以逆向查找
template <typename BidirectionalIterator1 ,typename BidirectionalIterator2>
BidirectionalIterator1 __my_find_end(BidirectionalIterator1 first1,BidirectionalIterator1 last1,BidirectionalIterator2 first2,BidirectionalIterator2 last2,
                                bidirectional_iterator_tag,bidirectional_iterator_tag)
{
    typedef std::reverse_iterator<BidirectionalIterator1> reviter1;
    typedef std::reverse_iterator<BidirectionalIterator2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = search(reviter1(last1),rlast1,reviter2(last2),rlast2);
    if(rresult==rlast1){
        //没找到
        return last1;
    }else{
        BidirectionalIterator1 result=rresult.base();//转回正常（非逆向）迭代器
        std::advance(result,-std::distance(first2,last2));//调整回子序列起头处
        return result;
    }
}

//find_first_of,在[first1,last1)中找到第一次出现[first2,last2)中任意一个元素的地方
template <typename InputIterator,typename ForwardIterator>
InputIterator my_find_first_of(InputIterator first1,InputIterator last1,ForwardIterator first2,ForwardIterator last2){
    for(;first1!=last1;first1++){
        for(ForwardIterator itr=first2;itr!=last2;itr++){
            if(*first1==*itr){
                return first1;
            }
        }
    }
    return last1;
}

template <typename InputIterator,typename ForwardIterator,typename BinaryOperation>
InputIterator my_find_first_of(InputIterator first1,InputIterator last1,ForwardIterator first2,ForwardIterator last2,BinaryOperation bop){
    for(;first1!=last1;first1++){
        for(ForwardIterator itr=first2;itr!=last2;itr++){
            if(bop(*first1,*itr)){
                return first1;
            }
        }
    }
    return last1;
}

//for_each，仿函数不能修改迭代器所指内容，只能读取
template <typename InputIterator,typename Function>
Function my_for_each(InputIterator first,InputIterator last,Function f){
    for(;first!=last;first++){
        f(*first);
    }
    return f;
}

//generate，将gen运算结果填写在区间中
template <typename ForwardIterator,typename Generator>
void my_generate(ForwardIterator first,ForwardIterator last,Generator gen){
    for(;first!=last;first++){
        *first=gen();
    }
}
//gen运算结果填写在first开始的n个元素上
template <typename ForwardIterator,typename Generator,typename Size>
void my_generate(ForwardIterator first,ForwardIterator last,Size n,Generator gen){
    for(;n>0;--n,first++){
        *first=gen();
    }
    return first;
}

#endif

//includes用于判断有序集合，s2中的每个元素是否在s1中存在,默认递增
template <typename InputIterator1,typename InputIterator2>
bool my_includes(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2){
    while(first1!=last1 && first2!=last2){
        if(*first1>*first2){
            return false;
        }
        else if(*first1<*first2){
            first1++;
        }
        else{
            first1++;
            first2++;
        }
    }
    return first2==last2;
}

template <typename InputIterator1,typename InputIterator2,typename Compare>
bool my_includes(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2,Compare comp){
    while(first1!=last1 && first2!=last2){
        if(comp(*first2,*first1)){
            return false;
        }
        else if(comp(*first1,*first2)){
            first1++;
        }
        else{
            first1++;
            first2++;
        }
    }
    return first2==last2;
}

//max_element,返回序列中最大的元素
template<typename ForwardIterator>
ForwardIterator my_max_element(ForwardIterator first,ForwardIterator last){
    if(first==last) return first;
    ForwardIterator result=first;
    for(;first!=last;first++){
        if(*result<*first){
            result=first;
        }
    }
    return result;
}

template<typename ForwardIterator,typename Compare>
ForwardIterator my_max_element(ForwardIterator first,ForwardIterator last,Compare comp){
    if(first==last) return first;
    ForwardIterator result=first;
    for(;first!=last;first++){
        if(comp(*result,*first)){
            result=first;
        }
    }
    return result;
}

//min_element,返回序列中最小的元素
template<typename ForwardIterator>
ForwardIterator my_min_element(ForwardIterator first,ForwardIterator last){
    if(first==last) return first;
    ForwardIterator result=first;
    for(;first!=last;first++){
        if(*result>*first){
            result=first;
        }
    }
    return result;
}

template<typename ForwardIterator,typename Compare>
ForwardIterator my_min_element(ForwardIterator first,ForwardIterator last,Compare comp){
    if(first==last) return first;
    ForwardIterator result=first;
    for(;first!=last;first++){
        if(comp(*first,*result)){
            result=first;
        }
    }
    return result;
}

//merge,将两个有序容器合并为一个
template <typename InputIterator1,typename InputIterator2,typename OutputIterator>
OutputIterator my_merge(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2,OutputIterator result){
    while(first1!=last1 && first2!=last2){
        if(*first2<*first1){
            *result=*first2;
            first2++;
        }
        else{
            *result=*first1;
            first1++;
        }
        result++;
    }
    return copy(first2,last2,copy(first1,last1,result));
}

template <typename InputIterator1,typename InputIterator2,typename OutputIterator,typename Compare>
OutputIterator my_merge(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,InputIterator2 last2,OutputIterator result,Compare comp){
    while(first1!=last1 && first2!=last2){
        if(comp(*first2,*first1)){
            *result=*first2;
            first2++;
        }
        else{
            *result=*first1;
            first1++;
        }
        result++;
    }
    return copy(first2,last2,copy(first1,last1,result));
}

//partition

//remove

//remove_copy

//remove_if


//remove_copy_if

//replace

//replace_copy


//replace_if

//replace_copy_if

//reverse

//reverse_copy

//rotate

//rotate_copy

//search

//search_n

//swap_ranges

//transform

//unique

//unique_copy