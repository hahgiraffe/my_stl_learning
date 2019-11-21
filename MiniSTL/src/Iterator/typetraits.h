/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 21:53:11
 * @Description: typetraits
 */
#ifndef MINISTL_SRC_ALLOCATOR_ITERATOR_TYPETRAITS_H
#define MINISTL_SRC_ALLOCATOR_ITERATOR_TYPETRAITS_H

namespace MINISTL{

    //表示真假
    struct __true_type{ };
    struct __false_type{ };

    //默认情况下，五种都默认为保守值，自定义类型为重要
    template <typename T>
    struct _type_traits{
        typedef __false_type has_trivial_default_constructor;
        typedef __false_type has_trivial_copy_constructor;
        typedef __false_type has_trivial_assignment_operator;
        typedef __false_type has_trivial_destructor;
        typedef __false_type is_POD_type;
    };

    //以下基础类型都进行特化或者偏特化，表示不重要
    
    template <> 
    struct _type_traits<bool> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<char> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<signed char> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned char> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<short> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned short> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<int> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned int> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<long> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned long> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<long long> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned long long> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<float> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<double> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<long double> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    //以下为偏特化
    template <typename T> 
    struct _type_traits<T*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
    
    template <typename T> 
    struct _type_traits<const T*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    //char特化
    template <> 
    struct _type_traits<char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<unsigned char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<signed char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<const char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<const unsigned char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };

    template <> 
    struct _type_traits<const signed char*> {
        typedef __true_type has_trivial_default_constructor;
        typedef __true_type has_trivial_copy_constructor;
        typedef __true_type has_trivial_assignment_operator;
        typedef __true_type has_trivial_destructor;
        typedef __true_type is_POD_type;
    };
}   //MINISTL

#endif //MINISTL_SRC_ALLOCATOR_ITERATOR_TYPETRAITS_H