/*
 * @Author: haha_giraffe
 * @Date: 2019-12-09 09:44:39
 * @Description: hashtable实现
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHTABLE_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHTABLE_H
#include "../../Iterator/stl_iterator.h"
#include "../../Allocator/allocator.h"
#include "../../Container/Sequence/vector.h"
#include "../../Algorithm/algorithm.h"
#include "./hash_fun.h"

namespace MINISTL{

//前置声明
template <typename Value> struct hash_node;
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
struct hashtable;
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
struct hashtable_iterator;

//buckets的个数只能是质数
static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] = {
    53ul,        97ul,        193ul,       389ul,       769ul,        1543ul,       3079ul,
    6151ul,      12289ul,     24593ul,     49157ul,     98317ul,      196613ul,     393241ul,
    786433ul,    1572869ul,   3145739ul,   6291469ul,   12582917ul,   25165843ul,   50331653ul,
    100663319ul, 201326611ul, 402653189ul, 805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
};
//大于等于n的第一个质数
inline unsigned long __stl_next_prime(unsigned long n){
    const unsigned long* first = __stl_prime_list;
    const unsigned long* last = __stl_prime_list + __stl_num_primes;
    const unsigned long* pos = MINISTL::lower_bound(first, last, n);    //lower_bound还没有实现(DOWN)
    return pos == last ? *(last-1) : *pos;
}

template <typename Value>
struct hash_node{
    hash_node* next;
    Value val;
};

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
struct hashtable_iterator{
    typedef hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> __hashtable;
    typedef hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> iterator;
    typedef hash_node<Value> node;

    typedef forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef Value& reference;
    typedef Value* pointer;

    node* cur;
    __hashtable* ht;
    
    hashtable_iterator(node* c, __hashtable* h) : cur(c), ht(h) { }
    hashtable_iterator() { }
    reference operator*() const { return cur->val;}
    pointer operator->() const { return &(cur->val);}
    iterator& operator++();
    iterator operator++(int);
    bool operator == (const iterator& it) const { return cur == it.cur;}
    bool operator != (const iterator& it) const { return cur != it.cur;}
};

//前缀++,这里要注意一点，hash采用链表法防止冲突，所以当一个链表中没有next的时候，++就会调到下一个bucket的第一个节点
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator ++ (){
    const node* old = cur;
    cur = cur->next;
    if(!cur){
        size_type bucket = ht->bkt_num(old->val);
        while(!cur && ++bucket < ht->bucket_count()){
            cur = ht->buckets[bucket];
        }
    }
    return *this;
}

//后缀++
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator ++ (int){
    iterator tmp = *this;
    ++*this;
    return tmp;
}

//模板参数： Value值类型，Key键类型，HashFun哈希函数，ExtractKey从节点中取键的仿函数，EqualKey判断键是否相同的仿函数，Alloc分配器默认使用二级分配器
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc = __default_alloc>
class hashtable{
public:
    typedef HashFun hasher;
    typedef EqualKey key_equal;
    typedef Key key_type;
    typedef Value value_type;
    typedef Value* pointer;
    typedef Value& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc> iterator;

private:
    //functor hash
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef hash_node<Value> node;
    typedef allocator<node, Alloc> node_allocator;
    
    size_type num_elements;                 //hash_table中元素个数

public:
    MINISTL::vector<node*, Alloc> buckets;  //vector存储的buckets

    //memory control
    node* new_node(const value_type& v){
        node* n = node_allocator::allocate();
        n->next = 0;
        try
        {
            construct(&n->val, v);
            return n;
        }
        catch(const std::exception& e)
        {
            destroy(&n->val);
            std::cerr << e.what() << '\n';
        }
    }
    void delete_node(node* n){
        destroy(&n->val);
        node_allocator::deallocate(n);
    }

    //ctor dtor
    hashtable(size_type n, const HashFun& hf, const EqualKey& ek)
        :hash(hf), equals(ek), get_key(ExtractKey()), num_elements(0){
            initialize_buckets(n);
    }
    void initialize_buckets(size_type n){
        //找到第一个大于等于n的质数，并在vector中构造n_buckets个空元素
        const size_type n_buckets = next_size(n);
        //TODO vector::reserve 和 vector::insert都没有实现(DOWN)
        buckets.reserve(n_buckets);
        buckets.insert(buckets.end(), n_buckets, static_cast<node*>(nullptr));
        num_elements = 0;
    }

    //public funciton
    hasher hash_funct() const { return hash;}
    key_equal key_eq() const { return equals;}
    size_type size() const { return num_elements; }
    size_type max_size() const { return size_type(-1); }
    size_type bucket_count() const { return buckets.size();}                                //返回bucket个数
    bool empty() const { return num_elements == 0 ? true : false;}
    size_type next_size(size_type n) const { return MINISTL::__stl_next_prime(n); }
    size_type max_bucket_count() const { return __stl_prime_list[__stl_num_primes - 1]; }   //返回buckets个数最大值，当前设置为4294967291ul
    void resize(size_type num);
    void clear();
    void copy_from(const hashtable& ht);
    iterator find(const key_type& v);
    reference find_or_insert(const value_type &);   //for map used
    size_type count(const key_type& v);
    pair<iterator, iterator> equal_range(const key_type& k);
    size_type elems_in_bucket(size_type i) {
        node* tmp = buckets[i];
        size_type res = 0;
        while(tmp){
            tmp = tmp->next;
            res++;
        }
        return res;
    }
    iterator begin(){ 
        for(size_type n = 0; n < buckets.size(); ++n){
            if(buckets[n]){
                return iterator(buckets[n], this);
            }
        }
        return end();
    }
    iterator end(){
        return iterator(NULL, this);
    }
    void swap(hashtable& hst){
        MINISTL::swap(hash, hst.hash);
        MINISTL::swap(equals, hst.equals);
        MINISTL::swap(get_key, hst.get_key);
        MINISTL::swap(num_elements, hst.num_elements);
        buckets.swap(hst.buckets);
    }
    //insert_unique
    pair<iterator, bool> insert_unique(const value_type& v);
    pair<iterator, bool> insert_unique_noresize(const value_type& v);
    template <class InputIterator> 
    void insert_unique(InputIterator first, InputIterator last) {
        insert_unique(first, last, iterator_category(first));
    }
    template <class ForwardIterator> 
    void insert_unique(ForwardIterator, ForwardIterator, forward_iterator_tag);
    template <class InputIterator> 
    void insert_unique(InputIterator, InputIterator, input_iterator_tag);
    
    //insert_equal
    iterator insert_equal(const value_type& v);
    iterator insert_equal_noresize(const value_type& v);
    template <typename InputIterator>
    void insert_equal(InputIterator first, InputIterator last){
        insert_equal(first, last, iterator_category(first));
    }
    template <class ForwardIterator> 
    void insert_equal(ForwardIterator, ForwardIterator, forward_iterator_tag);
    template <class InputIterator> 
    void insert_equal(InputIterator, InputIterator, input_iterator_tag);
    
    //erase
    size_type erase(const key_type& v);
    void erase(const iterator&);
    // void erase(iterator, iterator);  
    
    //bkt_num,计算实值在哪个bucket中
    size_type bkt_num_key(const key_type& key, size_t n) const { return hash(key) % n;}
    size_type bkt_num_key(const key_type& key) const { return bkt_num_key(key, buckets.size());}
    size_type bkt_num(const value_type& v) const { return bkt_num_key(get_key(v)); }
    size_type bkt_num(const value_type& v, size_t n) const { return bkt_num_key(get_key(v), n); }
};

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::resize(size_type num){
    const size_type old_n = buckets.size();
    //如果resize的大小大于原来的bucket大小则进行更换
    if(num > old_n){
        // printf("999999\n");
        const size_type n = next_size(num);
        if(n > old_n){
            MINISTL::vector<node*, Alloc> tmp(n, (node*)0);
            try
            {
                //处理旧vector中的数据，将其放入tmp中
                for(size_type bucket = 0; bucket < old_n; ++bucket){
                    node* first = buckets[bucket];  //旧vector中存储的指针
                    while(first){
                        //首先计算节点出在新bucket中的位置
                        size_type new_bucket = bkt_num(first->val, n);
                        //旧buckets指向下一个节点
                        buckets[bucket] = first->next;
                        //当前节点插入新的bucket内，头插入，使其称为链上第一个节点
                        first->next = tmp[new_bucket];
                        tmp[new_bucket] = first;
                        //赋值下一个旧bucket的first
                        first = buckets[bucket];
                    }
                }
                buckets.swap(tmp);      //vector::swap
            }
            catch(const std::exception& e)
            {
                clear();
                std::cerr << e.what() << '\n';
            }
        }
    }
}

//清空所有的bucket，但是bucket的空间大小未释放
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::clear(){
    for(size_type i = 0; i<buckets.size(); ++i){
        node* cur = buckets[i];
        while(cur){
            node* next = cur->next;
            delete_node(cur);
            cur = next;
        }
        buckets[i] = 0;
    }
    num_elements = 0;
}

//复制整个hashtable
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::copy_from(const hashtable& ht){
    buckets.clear();
    buckets.reserve(ht.buckets.size());
    buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
    try
    {
        for(size_type i = 0; i < ht.buckets.size(); ++i){
            if(const node* cur = ht.buckets[i]){
                node* copy = new_node(cur->val);
                for(node* next = cur->next; next; next = cur->next){
                    copy->next = new_node(next->val);
                    copy = copy->next;
                }
            }
        }
        num_elements = ht.num_elements;
    }
    catch(const std::exception& e)
    {
        clear();
        std::cerr << e.what() << '\n';
    }
}
//insert

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
pair<typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator, bool> 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_unique(const value_type& v){
    //先判断是否需要扩充表格，如果需要则先扩张
    resize(num_elements + 1);
    return insert_unique_noresize(v);
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
template <class ForwardIterator> 
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_unique(ForwardIterator first, ForwardIterator last, forward_iterator_tag){
    size_type n = distance(first, last);
    resize(num_elements + n);
    for(; n>0; --n, ++first){
        insert_unique_noresize(*first);
    }
}
    
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
template <class InputIterator> 
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_unique(InputIterator first, InputIterator last, input_iterator_tag){
    for(first; first != last; ++first){
        insert_unique(*first);
    }
}
 
//不需要resize时候插入不可重复的节点
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
pair< typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator, bool> 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const value_type& v){
    const size_type n = bkt_num(v);
    node* first = buckets[n];
    //在buckets[n]的链表中遍历查找,如果已经存在则返回false
    for(node* cur = first; cur ; cur = cur->next){
        const key_type curval = get_key(cur->val);
        const key_type vval = get_key(v);
        if(equals(get_key(cur->val), get_key(v))){
            return pair<iterator, bool>(iterator(cur, this), false);
        }
    }
    // printf("1111111\n");
    //如果没有找到则插入到对应bucket的头结点
    node* tmp  = new_node(v);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return pair<iterator, bool>(iterator(tmp, this), true);
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_equal(const value_type& v){
    resize(num_elements + 1);
    return insert_equal_noresize(v);
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_equal_noresize(const value_type& v){
    const size_type n = bkt_num(v);
    node* first = buckets[n];
    for(node* cur = first; cur; cur = cur->next){
        if(equals(get_key(cur->val), get_key(v))){
            //如果发现重复值的节点则在其前面插入并返回
            node *tmp = new_node(v);
            tmp->next = cur->next;
            cur->next = tmp;
            ++num_elements;
            return iterator(tmp, this);
        }
    }
    //没有重复值，则头插入
    node *tmp = new_node(v);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return iterator(tmp, this);
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
template <class ForwardIterator> 
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_equal(ForwardIterator first, ForwardIterator last, forward_iterator_tag){
    size_type n = distance(first, last);
    resize(num_elements + n);
    for (; n > 0; --n, ++first){
        insert_equal_noresize(*first);
    }
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
template <class InputIterator> 
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::insert_equal(InputIterator first, InputIterator last, input_iterator_tag){
    for (; first != last; ++first){
        insert_equal(*first);
    }
}
 

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator 
hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::find(const key_type& v){
    size_type n = bkt_num_key(v);
    node* first;
    for(first = buckets[n]; first && !equals(get_key(first->val), v); first = first->next){ }
    return iterator(first, this);
}


template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::size_type 
hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::count(const key_type& v){
    const size_type n = bkt_num_key(v);
    size_type result = 0;
    for(node* cur = buckets[n]; cur; cur = cur->next){
        if(equals(get_key(cur->val), v)){
            ++result;
        }
    }
    return result;
}


template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
pair<typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator, typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::iterator> 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::equal_range(const key_type& k){
    const size_type n = bkt_num_key(k);
    //先找出bucket的n，然后在里面遍历
    for(node* first = buckets[n]; first; first = first->next){
        if(equals(get_key(first->val), k)){
            //如果找到first指针值则记录下，接着遍历找end
            for(node* cur = first->next; cur; cur = cur->next){
                if(!equals(get_key(cur->val), k)){
                    return pair<iterator, iterator>(iterator(first, this), iterator(cur, this));
                }
            }
            //如果bucket[n]中first后面都是k值，则往后遍历n，如果有则返回
            for(size_type m = n+1; m < buckets.size(); ++m){
                if(buckets[m]){
                    return pair<iterator, iterator>(iterator(first, this), iterator(buckets[m], this));
                }
            }
            //如果bucket[n]之后都没有了则返回end
            return pair<iterator, iterator>(iterator(first, this), end());
        }
    }
    return pair<iterator, iterator>(end(), end());
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::size_type 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::erase(const key_type& v){
    //整体思路就是首先找到对应的bucket，然后以此遍历，过程就是单链表中删除一个元素
    const size_type n = bkt_num_key(v);
    node* first = buckets[n];
    size_type erased = 0;
    if(first){
        node* cur = first;
        node* next = cur->next;
        while(next){
            if(equals(get_key(next->val), v)){
                cur->next = next->next;
                delete_node(next);
                next = cur->next;
                ++erased;
                --num_elements;
            }
            else{
                cur = next;
                next = cur->next;
            }
        }
        if(equals(get_key(first->val), v)){
            buckets[n] = first->next;
            delete_node(first);
            ++erased;
            --num_elements;
        }
    }
    return erased;
}

template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::erase(const iterator& it){
    node* p = it.cur;
    if(p){
        size_type n = bkt_num_key(p->val);
        node* cur = buckets[n];
        if(cur == p){
            buckets[n] = cur->next;
            delete_node(cur);
            --num_elements;
        }
        else{
            node *next = cur->next;
            while(next){
                if(next == p){
                    cur->next = next->next;
                    delete_node(next);
                    --num_elements;
                    break;
                }
                else {
                    cur = next;
                    next = cur->next;
                }
            }
        }
    }
}

// template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
// void hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::erase(iterator first, iterator last){
//     size_type f_bucket = first.cur ? bkt_num(first.cur->val) : buckets.size();
//     size_type l_bucket = last.cur ? bkt_num(last.cur->val) : buckets.size();
//     if(first.cur == last.cur){
//         return;
//     }
//     else{

//     }
// }

//用于map的[],先查找如果没有找到则插入元素，找到则返回
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
typename hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::reference 
hashtable<Value, Key,HashFun, ExtractKey, EqualKey, Alloc>::find_or_insert(const value_type & v){
    resize(num_elements+1);
    size_type n = bkt_num(v);
    node* first = buckets[n];
    for(node* cur = first; cur ; cur = cur->next){
        if(equals(get_key(cur->val), get_key(v))){
            return cur->val;
        }
    }
    //如果没有找到则在头结点进行插入
    node* tmp = new_node(v);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return tmp->val;
}
 
template <typename Value, typename Key, typename HashFun, typename ExtractKey, typename EqualKey, typename Alloc>
inline bool operator==(hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& lhs,
                hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& rhs) {
    if (lhs.buckets.size() != rhs.buckets.size())
        return false;
    for (int n = 0; n < lhs.buckets.size(); ++n) {
        typename hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::node *cur1 = lhs.buckets[n];
        typename hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::node *cur2 = rhs.buckets[n];
        for (; cur1 && cur2 && cur1->val == cur2->val; cur1 = cur1->next, cur2 = cur2->next) { }
        if (cur1 || cur2)
            return false;
    }
    return true;
}

}       //namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHTABLE_H

