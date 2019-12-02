/*
 * @Author: haha_giraffe
 * @Date: 2019-12-01 12:05:02
 * @Description: stack以deque为底层实现
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_STACK_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_STACK_H
#include "./deque.h"

namespace MINISTL{

template<typename T, typename Sequence = deque<T> >
class stack{
public:
    bool operator == (const stack<T, Sequence>& y){
        return this->c == y.c;
    }
    bool operator < (const stack<T, Sequence>& y){
        return this->c < y.c;
    }
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
protected:
    Sequence c; //底层deque容器
public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.back(); }
    // const_reference top() { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_back(); }
};

// template <typename T, typename Sequence>
// bool operator == (const stack<T, Sequence>& x, const stack<T, Sequence>& y){
//     // return x.c == y.c;
// }

// template <typename T, typename Sequence>
// bool operator < (const stack<T, Sequence>& x, const stack<T, Sequence>& y){
//     return x.c < y.c;
// }


}

#endif //MINISTL_SRC_CONTAINER_SEQUENCE_STACK_H
