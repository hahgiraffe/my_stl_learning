/*
 * @Author: haha_giraffe
 * @Date: 2019-11-21 16:50:39
 * @Description: Iterator主体
 */
#ifndef MINISTL_SRC_ALLOCATOR_ITERATOR_STL_ITERATOR_H
#define MINISTL_SRC_ALLOCATOR_ITERATOR_STL_ITERATOR_H
#include <stddef.h>

namespace MINISTL{

    //iterator类型
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };


    template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T*>
    struct iterator
    {
        typedef Category iterator_category; //迭代器类型
        typedef T value_type;               //迭代器指向值类型
        typedef Distance difference_type;   //距离
        typedef Pointer pointer;            //指针
        typedef Reference reference;        //引用
    };

    //迭代器萃取剂
    template <typename Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    //偏特化
    template <typename T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;   
    };
    
    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;   
    };
    
    //萃取出迭代器类型
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&){
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    //萃取出两个迭代器之间的距离distance type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    //萃取出迭代器所指对象value type
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    //以下为整组distance函数
    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::diffrence_type __distance(InputIterator first, InputIterator last, input_iterator_tag) {
        iterator_traits<InputIterator>::diffrence_type n = 0;
        while (first != last)
            ++first, ++n;
        return n;
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::diffrence_type __distance(InputIterator first, InputIterator last, random_access_iterator_tag) {
        return last - first;
    }

    template <class InputIterator>
    inline typename iterator_traits<InputIterator>::diffrence_type distance(InputIterator first, InputIterator last) {
        typename iterator_traits<InputIterator>::iterator_category category;
        return __distance(first, last, category());
    }

    //以下为整组advance函数
    template <class InputIterator, class Distance>
    inline void __advance(InputIterator &i, Distance n, input_iterator_tag) {
        while (n--) ++i;
    }

    template <class InputIterator, class Distance>
    inline void __advance(InputIterator &i, Distance n, bidirectional_iterator_tag) {
        if (n >= 0)
            while (n--) ++i;
        else
            while (n++) --i;
    }

    template <class InputIterator, class Distance>
    inline void __advance(InputIterator &i, Distance n, random_access_iterator_tag) {
        i += n;
    }

    template <class InputIterator, class Distance> inline void advance(InputIterator &i, Distance n) {
        __advance(i, n, iterator_traits<InputIterator>::iterator_category());
    }


}   //MINISTL

#endif //MINISTL_SRC_ALLOCATOR_ITERATOR_STL_ITERATOR_H