/*
 * @Author: haha_giraffe
 * @Date: 2019-12-06 11:37:41
 * @Description: map实现key-value对
 */

#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_MULTIMAP_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_MULTIMAP_H
#include "./rb_tree.h"
#include "../../Functor/stl_function.h"
namespace MINISTL{

// template <typename T1, typename T2>
// struct pair{
//     typedef T1 first_type;
//     typedef T2 second_type;
//     T1 first;
//     T2 second;
//     pair() : first(T1()), second(T2()) { }
//     pair(const T1& a, const T2& b)
//         : first(a), second(b) { }
// };

//Key为键的类型，T为值的类型，Compare为比较规则，Alloc为分配器
template <typename Key, typename T, typename Compare = less<Key>, typename Alloc = __default_alloc>
class multimap{
public:
    //注意这里定义的是键类型为Key(key_type) 值类型为T(data_type) 键值对类型为 pair<const Key, T>(value_type) 键不可变
    typedef Key key_type;
    typedef T data_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;  //键值对类型
    typedef Compare key_compare;
    
    //以下定义一个functor，默认根据key值进行比较
    class value_compare : public binary_function<value_type, value_type, bool> {
        friend class map<Key, T, Compare, Alloc>;
    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) { }
    public:
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

private:
    typedef rb_tree<key_type, value_type, select1st<value_type>, key_compare, Alloc> rep_type;
    rep_type t;

public:
    typedef typename rep_type::pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::iterator iterator;
    typedef typename rep_type::const_iterator const_iterator;
    //reverse_iterator
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

    //multimap运用insert_equal()
    //ctor
    multimap() : t(Compare()) { }
    explicit multimap(const Compare& comp) : t(comp) { }

    template <typename InputIterator>
    multimap(InputIterator first, InputIterator last)
        : t(Compare()) { t.insert_equal(first, last); }
    

    template <typename InputIterator>
    multimap(InputIterator first, InputIterator last, const Compare& comp)
        : t(comp) { t.insert_equal(first, last); }
    
    multimap(const map<Key, T, Compare, Alloc>& x) : t(x.t) { }

    multimap<Key, T, Compare, Alloc>& operator = (const multimap<Key, T, Compare, Alloc>& x){
        t = x.t;
        return *this;
    }

public:
    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return value_compare(t.key_comp()); }
    iterator begin() { return t.begin(); }
    iterator end() { return t.end(); }
    const_iterator begin() const { return t.begin(); }
    const_iterator end() const { return t.end(); }
    //reverse没有实现
    bool empty() const{ return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }
    void swap(map<Key, T, Compare, Alloc>& m) { t.swap(m.t); }
    void clear(){ t.clear(); }
    // operator [] 的实现，首先调用value_type构建一个键值对类型，然后调用insert插入，返回一个pair<>类型，
    T& operator [] (const key_type& k){
        return (*(insert(value_type(k , T())))).second;
    }

    //insert
    //这里应该用std::pair??应该测试一下
    iterator insert(const value_type& x){
        return t.insert_equal(x);
    }
    // iterator insert(iterator position, const value_type& x){
    //     return t.insert_euqal(position, x);
    // }
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last){
        t.insert_equal(first, last);
    }

    //erase
    void erase(iterator position){
        t.erase(position);
    }
    size_type erase(const key_type& x) { return t.erase(x); }
    void erase(iterator first, iterator last){
        t.erase(first, last);
    }

    //map测试
    iterator find(const key_type& x) { return t.find(x); }
    const_iterator find(const key_type& x) const { return t.find(x); }
    size_type count(const key_type& x) const { return t.count(x); }
    iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
    iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
    const_iterator lower_bound(const key_type& x) const { return t.lower_bound(x); }
    const_iterator upper_bound(const key_type& x) const { return t.upper_bound(x); }
    std::pair<iterator, iterator> equal_range(const key_type& x) { return t.equal_range(x); }
    std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const { return t.equal_range(x); }

};

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator == (const multimap<Key, T, Compare, Alloc>& x, const multimap<Key, T, Compare, Alloc>& y){
    return x.t == y.t;
}

template <typename Key, typename T, typename Compare, typename Alloc>
inline bool operator < (const multimap<Key, T, Compare, Alloc>& x, const multimap<Key, T, Compare, Alloc>& y){
    return x.t < y.t;
}

}   //namespace MINISTL

#endif // MINISTL_SRC_CONTAINER_ASSOCIATIVE_MAP_H
