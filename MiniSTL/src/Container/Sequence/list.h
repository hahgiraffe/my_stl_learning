/*
 * @Author: haha_giraffe
 * @Date: 2019-11-26 21:58:12
 * @Description: list双向链表实现
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_LIST_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_LIST_H
#include "../../Allocator/allocator.h"
#include "../../Iterator/stl_iterator.h"
#include "../../Algorithm/algorithm.h"
#include <stddef.h>

namespace MINISTL{

template <typename T>
class __list_node{
public:
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <typename T, typename Ref, typename Ptr>
class __list_iterator{
public:
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef ptrdiff_t difference_type;

    link_type node; //迭代器中指针指向list节点

    //ctor
    __list_iterator(link_type x) : node(x) { }
    __list_iterator() { }
    __list_iterator(const iterator& x) : node(x.node) { }

    bool operator == (const self& x) const { return node == x.node; }
    bool operator != (const self& x) const { return node != x.node; }
    reference operator * () const { return (*node).data; }
    pointer operator -> () const { return &(operator*()); }
    //++后缀
    self& operator ++ () {
        node = (link_type)((*node).next);
        return *this;
    }
    //++前缀
    self operator ++(int){
        self tmp = *this;
        ++*this;
        return tmp;
    }
    //--后缀
    self& operator -- () {
        node = (link_type)((*node).prev);
        return *this;
    }
    //--前缀
    self operator --(int){
        self tmp = *this;
        --*this;
        return tmp;
    }
};

template <typename T, typename Alloc = __default_alloc>
class list{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __list_iterator<T, T&, T*> iterator;

protected:
    typedef __list_node<T> list_node;
    typedef allocator<list_node, Alloc> list_node_allocator;
    
public:
    typedef list_node* link_type;   ///只需要一个指针即可表示环状双向链表
    iterator begin() const { return (link_type)((*node).next); }
    iterator end() const { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const {
        size_type res = 0;
        //这里distance调用有问题
        // return distance(begin(),end());
        iterator tmp = begin();
        size_type dis = 0;
        while(tmp != end()){
            ++tmp;
            dis++;
        }
        return dis;
    }
    reference front() const { return *begin(); }
    reference back() const { return *(--end()); }
protected:
    link_type node; //node节点表示指向置于尾部的一个空白节点
    
    //申请、释放、构造、析构(这里注意申请内存和构造的顺序，析构和释放内存的顺序)
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }
    link_type create_node(const T& x){
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }
    void destroy_node(link_type p){
        destroy(&p->data);
        put_node(p);
    }
    //默认构造函数
    void empty_initialize(){
        node = get_node();
        node->next = node;
        node->prev = node;
    }
    //注意是在position迭代器之前插入node
    iterator insert(iterator position, const T& x){
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }
    //transfer操作是一个内部操作，将连续范围内的节点迁移到某个特定位置,[first,last)插入到position前面
    void transfer(iterator position, iterator first, iterator last){
        if(position != last){
            (*(link_type((*last.node).prev))).next = position.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;
            link_type tmp = link_type((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }
public:
    list() { empty_initialize(); }
    template <typename Itr>
    list(Itr first, Itr last){
        empty_initialize();
        // insert(begin(), first, last)
        transfer(begin(),first,last);
    }
    void push_back(const T& x);
    void push_front(const T& x);
    iterator erase(iterator position);
    void pop_front();
    void pop_back();
    void clear();
    void remove(const T& value);
    void unique();
    //将x插入position前
    void splice(iterator position, list& x);
    void splice(iterator position, iterator first, iterator last);
    void splice(iterator position, list& x, iterator i);
    void reverse();
    void sort();
    void merge(list& x);
    void swap(list& rhs) { MINISTL::swap(node, rhs.node); }
};

template <typename T, typename Alloc>
void list<T, Alloc>::clear(){
    link_type cur = (link_type)node->next; //指向第一个节点
    while(cur != node){
        link_type tmp = cur;
        cur = (link_type) cur->next;
        destroy_node(tmp);
    }
    node->next = node;
    node->prev = node;
}

template <typename T, typename Alloc>
void list<T, Alloc>::remove(const T& value){
    iterator first = begin();
    iterator last = end();
    while(first != last){
        iterator next = first;
        ++next;
        if(*first == value) erase(first);
        first = next;
    }
}

//unique只移除连续且值相等的节点（保存一个）
template <typename T, typename Alloc>
void list<T, Alloc>::unique(){
    iterator first = begin();
    iterator last = end();
    if(first == last) return;
    iterator next = first;
    while(++next != last){
        if(*first == *next){
            erase(next);
        }
        else{
            first = next;
        }
        next = first;
    }

}

template <typename T, typename Alloc >
void list<T, Alloc>::push_back(const T& x){
    insert(end(), x);
}

template <typename T, typename Alloc >
void list<T, Alloc>::push_front(const T& x){
    insert(begin(), x);
}

template <typename T, typename Alloc >
void list<T, Alloc>::pop_back(){
    erase(begin());
}

template <typename T, typename Alloc >
void list<T, Alloc>::pop_front(){
    iterator tmp = end();
    erase(--tmp);
}

//删除position位置上的节点，返回指向下一个节点的迭代器，返回值如果是iterator是需要list限定的
template <typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator position){
    link_type next_node = link_type(position.node->next);
    link_type prev_node = link_type(position.node->prev);
    prev_node->next = next_node;
    next_node->prev = prev_node;
    destroy_node(position.node);
    return iterator(next_node);
}

//splice重载版本
template <typename T, typename Alloc>
void list<T, Alloc>::splice(iterator position, list& x){
    if(!x.empty()){
        transfer(position, x.begin(), x.end());
    }
}

//将[first,last)插入到position
template <typename T, typename Alloc>
void list<T, Alloc>::splice(iterator position, iterator first, iterator last){
    if(first != last){
        transfer(position, first, last);
    }
}
//将i所指元素插入到position中
template <typename T, typename Alloc>
void list<T, Alloc>::splice(iterator position, list<T, Alloc>& x, iterator i){
    iterator j = i;
    j++;
    if(position == i || position == j){
        return;
    }
    transfer(position, i, j);
}
    

template <typename T, typename Alloc>
void list<T, Alloc>::reverse(){
    //首先判断是否为空链表或仅有一个元素的链表
    if(node->next == node || link_type(node->next)->next == node){
        return;
    }
    iterator tmp = begin();
    ++tmp;
    while(tmp != end()){
        iterator old = tmp;
        ++tmp;
        transfer(begin(), old, tmp);
    }
}

//list因为不是RandomAccessIterator，不能采用std::sort，只能调用自己的sort（快排）
template <typename T, typename Alloc>
void list<T, Alloc>::sort(){
    if(node->next == node || link_type(node->next)->next == node ){
        return;
    }
    list<T, Alloc> carry;
    list<T, Alloc> count[64];
    int fill = 0;
    while(!empty()){
        carry.splice(carry.begin(), *this, begin());
        int i=0;
        while(i < fill && !count[i].empty()){
            count[i].merge(carry);
            carry.swap(count[i++]);
        }
        carry.swap(count[i]);
        if(i == fill) ++fill;
    }
    for(int i=1; i<fill; ++i){
        count[i].merge(count[i-1]);
    }
    swap(count[fill-1]);
}

//merge是将两个递增排序好的链表merge，双链表合并
template <typename T, typename Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x){
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();

    while(first1 != last1 && first2 != last2){
        if(*first1 <= *first2){
            ++first1;
        }
        else{
            iterator next = first2;
            transfer(first1, first2, ++next);
            first2 = next;
        }
    }
    if(first2 != last2) transfer(last1, first2, last2);
}

}   //MINISTL

#endif //MINISTL_SRC_CONTAINER_SEQUENCE_LIST_H