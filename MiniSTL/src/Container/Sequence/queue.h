/*
 * @Author: haha_giraffe
 * @Date: 2019-12-01 13:11:00
 * @Description: queue实现
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
#include "./deque.h"
#include "./vector.h"
#include "../../Algorithm/heap_algorithm.h"
#include "../../Functor/stl_function.h"

namespace MINISTL{

template<typename T, typename Sequence = deque<T>>
class queue{
public:
    bool operator == (const queue<T>& y){
        return this->c == y.c;
    }
    bool operator < (const queue<T>& y){
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
    reference back() { return c.back(); }
    reference front() { return c.front();}
    // const_reference top() { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
   
};

// template <typename T, typename Sequence>
// bool operator == (const queue<T, Sequence>& x, const queue<T, Sequence>& y){
//     return x.c == y.c;
// }

// template <typename T, typename Sequence>
// bool operator < (const queue<T, Sequence>& x, const queue<T, Sequence>& y){
//     return x.c < y.c;
// }

template <typename T, typename Sequence = vector<T>, typename Compare = MINISTL::less<typename Sequence::value_type>>
class priority_queue{
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;

protected:
    Sequence c;     //底层容器，默认为vector
    Compare comp;   //元素大小比较标准

public:
    priority_queue()
        :c(){ }
    explicit priority_queue(const Compare& x)
        :c(), comp(x){ }
    template <typename InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x)
        :c(first, last) ,comp(x) { MINISTL::make_heap(c.begin(), c.end(), comp); }
    template <typename InputIterator>
    priority_queue(InputIterator first, InputIterator last)
        :c(first, last) { MINISTL::make_heap(c.begin(), c.end()); }
public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.front(); }
    void push(const value_type& x){
        c.push_back(x);
        MINISTL::push_heap(c.begin(), c.end(), comp);
    }
    void pop(){
        MINISTL::pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

};

}
#endif //MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
 