/*
 * @Author: haha_giraffe
 * @Date: 2019-12-01 13:11:00
 * @Description: queue实现
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
#include "./deque.h"

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

}
#endif //MINISTL_SRC_CONTAINER_SEQUENCE_QUEUE_H
 