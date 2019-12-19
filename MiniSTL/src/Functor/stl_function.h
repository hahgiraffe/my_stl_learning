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

//greater_equal
template <typename T>
struct greater_equal : public binary_function<T, T, bool>{
    bool operator () (const T& x, const T& y) const { return x >= y; }
};

//less_equal
template <typename T>
struct less_equal : public binary_function<T, T, bool>{
    bool operator () (const T& x, const T& y) const { return x <= y; }
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

template <typename Pair>
struct select2st : public unary_function<Pair, typename Pair::second_type>{
    const typename Pair::second_type& operator()(const Pair& x) const{
        return x.second;
    }
};

//project1st, project2st 传回第几个参数，忽略其他参数
template <typename Arg1, typename Arg2>
struct project1st : public binary_function<Arg1, Arg2, Arg1>{
    Arg1 operator()(const Arg1& x, const Arg2& y) const {
        return x;
    }
};

template <typename Arg1, typename Arg2>
struct project2st : public binary_function<Arg1, Arg2, Arg2>{
    Arg2 operator()(const Arg1& x, const Arg2& y) const {
        return y;
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

//multiplies
template <typename T>
struct multiplies : public binary_function<T, T, T>{
    T operator() (const T& x, const T& y) const { return x * y; }
};

//divides
template <typename T>
struct divides : public binary_function<T, T, T>{
    T operator() (const T& x, const T& y) const { return x / y; }
};

//modulus
template <typename T>
struct modulus : public binary_function<T, T, T>{
    T operator() (const T& x, const T& y) const { return x % y; }
};

//negate
template <typename T>
struct negate : public unary_function<T, T>{
    T operator() (const T& x) const { return -x; }
};

//逻辑运算 And Or Not
template <typename T>
struct logical_and : public binary_function<T, T, boo>{
    bool operator() (const T& x, const T& y) const{
        return x && y;
    }
};

template <typename T>
struct logical_or : public binary_function<T, T, boo>{
    bool operator() (const T& x, const T& y) const{
        return x || y;
    }
};

template <typename T>
struct logical_not : public unary_function<T, boo>{
    bool operator() (const T& x) const{
        return !x;
    }
};

// Functor Adapters 
//not1 && not2 对返回值进行否定
template <typename Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type, bool>{
protected:
    Predicate pred;
public:
    explicit unary_negate(const Predicate& x) : pred(x) { }
    bool operator() (const typename Predicate::argument_type& x) const {
        return !pred(x);
    }
};

template <typename Predicate>
inline unary_negate<Predicate> not1(const Predicate& pred){
    return unary_negate<Predicate>(pred);
}

template <typename Predicate>
class binary_negate : public binary_function<typename Predicate::first_argument_type, typename Predicate::second_argument_type, bool>{
protected:
    Predicate pred;
public:
    explicit binary_negate(const Predicate& x) : pred(x) { }
    bool operator() (const typename Predicate::first_argument_type& x, const Predicate::second_argument_type& y) const {
        return !pred(x, y);
    }
};

template <typename Predicate>
inline binary_negate<Predicate> not2(const Predicate& pred){
    return binary_negate<Predicate>(pred);
}

// bind1nd && bind2nd
template <typename Operation>
class binder1st : public unary_function<typename Operation::second_argumnet_type, typename Operation::result_type>{
protected:
    Operation op;
    typename Operation::first_argument_type value;

public:
    binder1st(const Operation& x, const typename Operation::first_argument_type& y) 
        :op(x), value(y){ }
    typename Operation::result_type operator()(const typename Operation::second_argument_type& x) const{
        return op(value, x);
    }
};

template <typename Operation, typename T>
inline binder1st<Operation> bind1st(const Operation& op, const T& x){
    typedef typename Operation::first_argument_type arg1_type;
    return binder1st<Operation>(op, arg1_type);
}

template <typename Operation>
class binder2nd : public unary_function<typename Operation::first_argumnet_type, typename Operation::result_type>{
protected:
    Operation op;
    typename Operation::second_argument_type value;

public:
    binder2nd(const Operation& x, const typename Operation::second_argument_type& y) 
        :op(x), value(y){ }
    typename Operation::result_type operator()(const typename Operation::first_argument_type& x) const{
        return op(x, value);
    }
};

template <typename Operation, typename T>
inline binder2nd<Operation> bind2nd(const Operation& op, const T& x){
    typedef typename Operation::second_argument_type arg2_type;
    return binder2nd<Operation>(op, arg2_type);
}

}   //namespace MINISTL

#endif //MINISTL_SRC_FUNCTOR_STL_FUNCTION_H