/*
 * @Author: haha_giraffe
 * @Date: 2019-12-03 10:42:21
 * @Description: slist单链表的实现（包括ForwardIterator迭代器）
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUNCE_SLIST_H
#define MINISTL_SRC_CONTAINER_SEQUNCE_SLIST_H
#include "../../Allocator/allocator.h"
#include "../../Iterator/stl_iterator.h"
namespace MINISTL{

//单链表节点基本结构
struct __slist_node_base{
    __slist_node_base* next;
};

//单链表节点结构
template <typename T>
struct __slist_node : public __slist_node_base{
    T data;
};

//插入新节点到某节点之后
inline __slist_node_base* __slist_make_link(__slist_node_base* prev_node, __slist_node_base* new_node){
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    return new_node;    
}

//某个单链表的长度
inline size_t __slist_size(__slist_node_base* node){
    size_t result = 0;
    for( ; node != 0; node = node->next)
        ++result;
    return result;
}

//slist_iterator基础结构
struct __slist_iterator_base{
    //iterator的型别
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef forward_iterator_tag iterator_category;
    
    __slist_node_base* node;   //指向的节点
    __slist_iterator_base(__slist_node_base* x) : node(x) { }
    void incr(){ node = node->next; }   //前进一个节点
    bool operator == (const __slist_iterator_base& x) const {
        return node == x.node;
    }
    bool operator != (const __slist_iterator_base& x) const {
        return node != x.node;
    }
};

//slist_iterator结构
template <typename T, typename Ref, typename Ptr>
struct __slist_iterator : public __slist_iterator_base{
    typedef __slist_iterator<T, T&, T*> iterator;
    typedef __slist_iterator<T, const T&, const T*> const_iterator;
    typedef __slist_iterator<T, Ref, Ptr> self;

    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __slist_node<T> list_node;

    __slist_iterator(list_node* x) : __slist_iterator_base(x) { }
    __slist_iterator() : __slist_iterator_base(0) { }
    __slist_iterator(const iterator& x) : __slist_iterator_base(x.node) { }

    //ForwardIterator只有单向的迭代器
    reference operator * () const { return ((list_node*)node)->data; }  
    pointer operator -> () const { return &(operator *()); }
    self& operator++(){
        incr();
        return *this;
    }
    self operator++(int){
        self tmp = *this;
        incr();
        return tmp;
    }
    
};

template <typename T, typename Alloc = __default_alloc>
class slist{
public:
    //定义type，用于traits萃取
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
    typedef __slist_iterator<T, T&, T*> iterator;
    typedef __slist_iterator<T, const T&, const T*> const_iterator;

private:
    //简单typedef一下
    typedef __slist_node<T> list_node;
    typedef __slist_node_base list_node_base;
    typedef __slist_iterator_base iterator_base;
    typedef allocator<list_node, Alloc> list_node_allocator;

    //申请空间，构造元素
    static list_node* create_node(const value_type& x){
        list_node* node = list_node_allocator::allocate();
        try
        {
            construct(&node->data, x);
            node->next = 0;
        }
        catch(const std::exception& e)
        {
            list_node_allocator::deallocate(node);
            std::cerr << e.what() << '\n';
        }
        return node;
        
    }
    //析构元素，释放空间
    static void destroy_node(list_node* node){
        destroy(&node->data);
        list_node_allocator::deallocate(node);
    }

private:
    list_node_base head;    //这里定义一个头结点（没有值），并不是指针

public:
    //ctor dtor
    slist() { head.next = 0; }
    ~slist() { clear(); }
    iterator begin() { return iterator((list_node*)head.next); }
    iterator end() { return iterator(0); }      //注意这里是新建一个指向0的节点
    size_type size() { return __slist_size(head.next); }
    bool empty() const { return head.next == 0; }
    void clear(){
        size_type sz = size();
        for(int i=0; i<sz; ++i){
            pop_front();
        }
    }
    void swap(slist& l){
        list_node_base* tmp = head.next;
        head.next = l.head.next;
        l.head.next = tmp;
    }
    reference front() { return ((list_node*)head.next)->data;}
    void push_front(const value_type& x){
        __slist_make_link(&head, create_node(x));
    }
    void pop_front(){
        list_node* node = (list_node*)head.next;
        head.next = node->next;
        destroy_node(node);
    }
    //slist不存在push_back和pop_back

};

}   //namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_SEQUNCE_SLIST_H

