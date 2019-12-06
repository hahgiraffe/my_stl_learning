/*
 * @Author: haha_giraffe
 * @Date: 2019-12-05 13:10:49
 * @Description: set实现，底层用红黑树
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_SET_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_SET_H
#include "../../Functor/stl_function.h"
#include "../../Allocator/allocator.h"
#include "./rb_tree.h"

namespace MINISTL{

template <typename Key, typename Compare = less<Key>, typename Alloc = __default_alloc>
class set{
public:
    //set中只存储key，所以比较函数和类型设置为一样的即可
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;

private:
    typedef rb_tree<key_type, value_type, MINISTL::identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t; //底层用红黑树的实例

public:
    typedef typename rep_type::const_pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::const_reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::const_iterator iterator;
    typedef typename rep_type::const_iterator const_iterator;
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

    //set用红黑树的insert_unique() multiset用insert_equal()
    //ctor
    set() : t(Compare()) { }
    explicit set(const Compare& comp)
        : t(comp){ }
    template <typename InputIterator>
    set(InputIterator first, InputIterator last)
        : t(Compare()) { t.insert_unique(first, last); }    
    template <typename InputIterator>
    set(InputIterator first, InputIterator last, const Compare& comp)
        : t(comp) { t.insert_unique(first, last); }    
    set(const set<Key, Compare, Alloc> &x ) : t(x.t) { }
    set<Key, Compare, Alloc>& operator = (const set<Key, Compare, Alloc>& x){
        t = x.t;
        return *this;
    }

    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return t.key_comp(); }
    iterator begin() const { return t.begin(); }
    iterator end() { return t.end(); }
    //reverse_iterator
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }
    void swap(set<Key, Compare, Alloc>& x){ t.swap(x.t); }  
    void clear() {t.clear();}

    //insert
    std::pair<iterator, bool> insert(const value_type& x){
        std::pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
        return std::pair<iterator, bool>(p.first, p.second);
    }
    //这是什么意思？
    // iterator insert(iterator position, const value_type& x){
    //     typedef typename rep_type::iterator rep_iterator;
    //     return t.insert_unique((rep_iterator&)position, x); //insert_unique还有一个重载
    // }
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last){
        t.insert_unique(first, last);
    }
    
    //erase
    void erase(iterator position){
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)position);
    }
    size_type erase(const key_type& x){
        return t.erase(x);
    }
    void erase(iterator first, iterator last){
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)first, (rep_iterator&)last);
    }

    iterator find(const key_type& x) { return t.find(x); }
    size_type count(const key_type& x) { return t.count(x); }
    //返回指向首个小于等于给定键的元素的迭代器
    iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
    //返回指向首个大于给定键的元素的迭代器
    iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
    //返回lower_bound和upper_bound
    std::pair<iterator, iterator> equal_range(const key_type& x){ return t.equal_range(x); }

};

template <typename Key, typename Compare, typename Alloc>
inline bool operator ==(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y){
    return x.t == y.t;
}

// template <typename Key, typename Compare, typename Alloc>
// inline bool operator <(const set<Key, Compare, Alloc>& x, const set<Key, Compare, Alloc>& y){
//     return x.t < y.t;
// }


}

#endif