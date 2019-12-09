/*
 * @Author: haha_giraffe
 * @Date: 2019-12-07 14:33:20
 * @Description: multiset实现
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_MULTISET_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_MULTISET_H
#include "../../Functor/stl_function.h"
#include "../../Allocator/allocator.h"
#include "./rb_tree.h"
namespace MINISTL{

template <typename Key, typename Compare = less<Key>, typename Alloc = __default_alloc>
class multiset{
public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    
private:
    typedef rb_tree<key_type, value_type, MINISTL::identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;

public:
    typedef typename rep_type::const_pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::const_reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::const_iterator iterator;
    typedef typename rep_type::const_iterator const_iterator;
    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

    multiset() :t(Compare()) { }
    template <typename InputIterator>
    multiset(InputIterator first, InputIterator last)
        :t(Compare()) { t.insert_equal(first, last); }
    template <typename InputIterator>
    multiset(InputIterator first, InputIterator last, const Compare& comp)
        :t(comp) { t.insert_equal(first, last); }
    multiset(const multiset<Key, Compare, Alloc> &x ) : t(x.t) { }
    multiset<Key, Compare, Alloc>& operator = (const multiset<Key, Compare, Alloc>& x){
        t = x.t;
        return *this;
    }

    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return t.key_comp(); }
    iterator begin() const { return t.begin(); }
    iterator end() const { return t.end(); }
    //reverse_iterator
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }
    void swap(multiset<Key, Compare, Alloc>& x){ t.swap(x.t); }  
    void clear() {t.clear();}
    
    iterator find(const key_type& x) const { return t.find(x); }
    size_type count(const key_type& x) { return t.count(x); }
    //返回指向首个小于等于给定键的元素的迭代器
    iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
    //返回指向首个大于给定键的元素的迭代器
    iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
    //返回lower_bound和upper_bound
    std::pair<iterator, iterator> equal_range(const key_type& x){ return t.equal_range(x); }

    //insert
    iterator insert(const value_type& x){
        return t.insert_equal(x);
    }
    template <typename InputIterator>
    iterator insert(InputIterator first, InputIterator last){
        t.insert_equal(first, last);
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

};

template <typename Key, typename Compare, typename Alloc>
inline bool operator ==(const multiset<Key, Compare, Alloc>& x, const multiset<Key, Compare, Alloc>& y){
    return x.t == y.t;
}

}   //MINISTL

#endif // MINISTL_SRC_CONTAINER_ASSOCIATIVE_MULTISET_H