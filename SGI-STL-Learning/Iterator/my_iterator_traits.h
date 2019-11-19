#include <cstddef>
#include <iostream>
#include <string>
//ierator设计主要有几个注意的地方
//首先就是traits的方式及作用

//五种迭代器类型input iterator/output iterator/Forward iterator
//Bidirectional iterator/Random Access Iterator

//五种迭代器型别（可以理解为迭代器的属性）value_type/difference_type/reference_type
//pointer_type/iterator_category

//五种迭代器类型及关系，使用的时候主要根据效率选择

namespace my_instance{
    
struct input_iterator_tag{ };
struct output_iterator_tag{ };
struct forward_iterator_tag : public input_iterator_tag{ };
struct bidirectional_iterator_tag :public forward_iterator_tag{ };
struct random_access_iterator_tag :public bidirectional_iterator_tag{ }; 


//这个是用来给Iterator继承的，以免忘记
template <typename Category ,typename T,typename Distance=ptrdiff_t,typename Pointer=T*,typename Referance=T& >
struct iterator{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Referance reference;
};

//traits
template <typename Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

//对原生指针的traits偏特化
template <typename T>
struct iterator_traits<T*>{
    typedef  random_access_iterator_tag iterator_category;
    typedef  T value_type;
    typedef  ptrdiff_t difference_type;
    typedef  T* pointer;
    typedef  T& reference;
};

//对原生指针point-to-const的traits偏特化
template <typename T>
struct iterator_traits<const T*>{
    typedef  random_access_iterator_tag iterator_category;
    typedef  T value_type;
    typedef  ptrdiff_t difference_type;
    typedef  T* pointer;
    typedef  T& reference;
};

//这个函数是用来得到Iterator的类型的
template <typename Iterator> //注意这个模板类型是根据参数Iterator自动生成的
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

//这个函数是用来得到Iterator的distance_type的
template <typename Iterator> //注意这个模板类型是根据参数Iterator自动生成的
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type*> (0);
}
//这个函数是用来得到Iterator的value_type的
template <typename Iterator> //注意这个模板类型是根据参数Iterator自动生成的
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
}

//-----------------------------------------------------------------------
//下面是对上面定义好的函数的使用。distace试求两个迭代器之间的距离

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first,InputIterator second,input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n=0;
    while(first!=second){
        ++first;++n;
    }
    std::cout<<"giraffe_success1";     //这里为什么不打印出来啊？？？
    return n;
}

template <typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first,RandomAccessIterator second,random_access_iterator_tag){
    std::cout<<"giraffe_success2";   //这里为什么不打印出来啊？？？
    return second-first;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first,InputIterator second,std::string &str){
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    std::cout<<str<<std::endl;
    return __distance(first,second,category());  //gdb调试后发现这里没有进入上面的
}



}




