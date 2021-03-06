/*
 * @Author: haha_giraffe
 * @Date: 2019-12-12 17:03:06
 * @Description: unordered_multiset
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTISET_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTISET_H
#include "../../Allocator/allocator.h"
#include "./hash_fun.h"
#include "./hashtable.h"
#include "../../Functor/stl_function.h"
#include "./map.h"  //MINISTL::pair

namespace MINISTL{

template <typename Value, typename HashFun = hash<Value>, typename EqualKey = equal_to<Value>, typename Alloc = __default_alloc>
class unordered_multiset{
    friend bool operator==(const unordered_multiset<Value, HashFun, EqualKey, Alloc>&, const unordered_multiset<Value, HashFun, EqualKey, Alloc>& );
private:
    //底层为一个hash表
    typedef hashtable<Value, Value, HashFun, identity<Value>, EqualKey, Alloc> ht;
    ht rep;

public:
    typedef typename ht::key_type key_type;
    typedef typename ht::value_type value_type;
    typedef typename ht::hasher hasher;
    typedef typename ht::key_equal key_equal;

    typedef typename ht::size_type size_type;
    typedef typename ht::difference_type difference_type;
    typedef typename ht::reference reference;
    typedef typename ht::pointer pointer;
    typedef typename ht::iterator iterator;

    hasher hash_funct() const { return rep.hash_funct(); }
    key_equal key_eq() const { return rep.key_eq(); }

public:
    //ctor,默认情况初始化hashtable为100和bucket
    unordered_multiset() : rep(100, hasher(), key_equal()){ }
    explicit unordered_multiset(size_type n) : rep(n, hasher(), key_equal()){ }
    unordered_multiset(size_type n, const hasher& hf) : rep(n, hf, key_equal()){ }
    unordered_multiset(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql){ }

    template<typename InputIterator>
    unordered_multiset(InputIterator first, InputIterator last) : rep(100, hasher(), key_equal()){
        rep.insert_equal(first, last);
    }
    template<typename InputIterator>
    unordered_multiset(InputIterator first, InputIterator last, size_type n) 
        : rep(n, hasher(), key_equal()){
        rep.insert_equal(first, last);
    }
    template<typename InputIterator>
    unordered_multiset(InputIterator first, InputIterator last, size_type n, const hasher& hf) 
        : rep(n, hf, key_equal()){
        rep.insert_equal(first, last);
    }
    template<typename InputIterator>
    unordered_multiset(InputIterator first, InputIterator last, size_type n, const hasher& hf, const key_equal& eql) 
        : rep(n, hf, eql){
        rep.insert_equal(first, last);
    }
public:
    size_type size() const { return rep.size(); }
    size_type max_size() const { return rep.max_size(); }
    bool empty() const { return rep.empty(); }
    void swap(unordered_multiset& s) {rep.swap(s.rep); }
    iterator begin() {return rep.begin(); }
    iterator end() { return rep.end(); }

    iterator insert(const value_type& obj){
        return rep.insert_equal(obj);
    }
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last){
        rep.insert_equal(first, last);
    }
    iterator insert_noresize(const value_type& v){
        return rep.insert_equal_noresize(v);
    }
    iterator find(const key_type& key) { return rep.find(key); }
    size_type count(const key_type& key) { return rep.count(key); }
    void clear() { rep.clear(); }
    pair<iterator, iterator> equal_range(const key_type& key) { return rep.equal_range(key); }
    size_type erase(const key_type& key) { return rep.erase(key); }
    void erase(iterator it) {rep.erase(it); }
    // void erase(iterator first, iterator last) {rep.erase(first, last); }

    void resize(size_type n){ rep.resize(n); }
    size_type bucket_count() { return rep.bucket_count(); }
    size_type max_bucket_count() { return rep.max_bucket_count(); }
    size_type elems_in_bucket(size_type n) const{ return rep.elems_in_bucket(n); }
};

template <typename Value, typename HashFun, typename EqualKey , typename Alloc>
inline bool operator == (const unordered_multiset<Value, HashFun, EqualKey, Alloc>& lhs, const unordered_multiset<Value, HashFun, EqualKey, Alloc>& rhs){
    return lhs.rep == rhs.rep;  
}

}   //namespace MINISTL

#endif  //MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTISET_H
