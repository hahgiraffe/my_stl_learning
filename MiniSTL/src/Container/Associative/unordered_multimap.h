/*
 * @Author: haha_giraffe
 * @Date: 2019-12-12 18:13:43
 * @Description: unordered_multimap
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTIMAP_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTIMAP_H
#include "../../Allocator/allocator.h"
#include "./hash_fun.h"
#include "./hashtable.h"
#include "../../Functor/stl_function.h"
#include "./map.h"  //MINISTL::pair


namespace MINISTL{

template <typename Key, typename T, typename HashFun = hash<Key>, typename EqualKey = equal_to<Key>, typename Alloc = __default_alloc>
class unordered_multimap{
    friend bool operator==(const unordered_multimap& , const unordered_multimap& );
private:
typedef hashtable<pair<Key, T>, Key, HashFun, MINISTL::select1st<pair<Key, T> >, EqualKey, Alloc> ht;
    ht rep; //底层hashtable实体

public:
    typedef typename ht::key_type key_type;
    typedef T data_type;
    typedef T mapped_type;
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
    //ctor
    unordered_multimap() : rep(100, hasher(), key_equal()) { }
    explicit unordered_multimap(size_type n) : rep(n, hasher(), key_equal()) { }
    unordered_multimap(size_type n, const hasher& hf) : rep(n, hf, key_equal()) { }
    unordered_multimap(size_type n, const hasher& hf, const key_equal& eq) : rep(n, hf, eq) { }
    
    template<typename InputIterator>
    unordered_multimap(InputIterator first, InputIterator last) : rep(100, hasher(), key_equal()) { rep.insert_equal(first, last); }
    template<typename InputIterator>
    unordered_multimap(InputIterator first, InputIterator last, size_type n) : rep(n, hasher(), key_equal()) { rep.insert_equal(first, last); }
    template<typename InputIterator>
    unordered_multimap(InputIterator first, InputIterator last, size_type n, const hasher& hf) : rep(n, hf, key_equal()) { rep.insert_equal(first, last); }
    template<typename InputIterator>
    unordered_multimap(InputIterator first, InputIterator last, size_type n, const hasher& hf, const key_equal& eq) : rep(n, hf, eq) { rep.insert_equal(first, last); }
    
    size_type size() const { return rep.size(); }
    size_type max_size() const { return rep.max_size(); }
    bool empty() const { return rep.empty(); }
    void swap(unordered_multimap& m) {rep.swap(m.rep); }
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
    T& operator [] (const key_type& key){ return rep.find_or_insert(value_type(key, T())).second; }             //rep.find_or_insert
    pair<iterator, iterator> equal_range(const key_type& key) { return rep.equal_range(key); }
    size_type erase(const key_type& key) { return rep.erase(key); }
    void erase(iterator it) {rep.erase(it); }
    // void erase(iterator first, iterator last) {rep.erase(first, last); }

    void resize(size_type n){ rep.resize(n); }
    size_type bucket_count() { return rep.bucket_count(); }
    size_type max_bucket_count() { return rep.max_bucket_count(); }
    size_type elems_in_bucket(size_type n) const{ return rep.elems_in_bucket(n); }

};

template <typename Key, typename T, typename HashFun , typename EqualKey, typename Alloc>
inline bool operator==(const unordered_multimap<Key, T, HashFun, EqualKey, Alloc>& lhs,
                        const unordered_multimap<Key, T, HashFun, EqualKey, Alloc>& rhs){
    return lhs.rep == rhs.rep;
}

}       //namespace MINISTL

#endif // MINISTL_SRC_CONTAINER_ASSOCIATIVE_UNORDERED_MULTIMAP_H
