/*
 * @Author: haha_giraffe
 * @Date: 2019-11-28 19:38:00
 * @Description: 双端队列deque,物理上是一个分段连续内存空间，逻辑上是一个头尾都可以增删的数据结构
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_DEQUE_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_DEQUE_H
#include "../../Allocator/allocator.h"
#include "../../Iterator/stl_iterator.h"
#include "../../Allocator/uninitialized.h"
#include "../../Algorithm/algorithm.h"

namespace MINISTL{

//deque_iterator特有的迭代器
//这个函数是计算每个缓冲区中可以存放多少个元素
inline size_t __deque_buf_size(size_t n, size_t sz){
    return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template <typename T, typename Ref, typename Ptr, size_t Bufsiz>
struct __deque_iterator {
    typedef __deque_iterator<T, T&, T*, Bufsiz> iterator;
    typedef __deque_iterator<T, const T&, const T*, Bufsiz> const_iterator;
    //缓冲区大小，当Bufsiz不为0时就为Bufsiz，其实可以可以给定一个默认值
    static size_t buffer_size() { return __deque_buf_size(Bufsiz, sizeof(T)); }

    //自定义迭代器型别
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;

    //指向的deque
    T* cur;             //指向缓冲区的当前元素
    T* first;           //指向缓冲区的头部元素
    T* last;            //指向缓冲区的尾部元素
    map_pointer node;   //指向map中心（分段连续内存空间）

    //从一个map节点跳到另一个节点，需要重置指针
    void set_node(map_pointer new_node){
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator *() const { return *cur; }
    pointer operator-> () const { return &(operator*()); }
    //两个迭代器相减，输出之间的距离
    difference_type operator - (const self& x) const{ 
        return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
    }
    //++ 无参数的即为前缀式
    self& operator ++ (){
        ++cur;
        if(cur == last){
            set_node(node+1);
            cur = first;
        }
        return *this;
    }
    //++ 有参数的即为后缀式
    self operator ++ (int){
        self tmp = *this;
        ++*this;
        return tmp;
    }
    //--
    self& operator -- (){
        if(cur == first){
            set_node(node-1);
            cur = last;
        }
        --cur;
        return *this;
    }
    //--
    self operator -- (int){
        self tmp = *this;
        --*this;
        return tmp;
    }
    //+= random_access
    self& operator += (difference_type n){
        difference_type offset = n + (cur - first);
        if(offset >= 0 && offset < difference_type(buffer_size())){
            //目标位置在同一缓存区
            cur += n;    
        }
        else{
            //不在同一缓冲区
            difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size()) : -difference_type((-offset - 1) / buffer_size()) -1;
            set_node(node + node_offset);
        }
    }
    //+ random_access    
    self operator + (difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }
    //-=
    self& operator -= (difference_type n) { return *this += -n; }
    //-
    self operator - (difference_type n) const {
        self tmp = *this;
        return tmp -= n;
    }

    reference operator [] (difference_type n) const { return *(*this + n); }

    bool operator == (const self& x) const { return cur == x.cur; }
    bool operator != (const self& x) const { return !(*this == x); }
    bool operator < (const self& x) const {
        return (node == x.node) ? (cur < x.cur) : (node < x.node );
    }
};


template <typename T, typename Alloc = __default_alloc, size_t Bufsize = 0>
class deque{
public:
    // bool operator == (const deque<T>& lhs, const deque<T>& rhs);
    typedef T value_type;
    typedef value_type* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __deque_iterator<T, T&, T*, Bufsize> iterator;
    typedef allocator<value_type, Alloc> data_allocator;
    typedef allocator<pointer, Alloc> map_allocator;

protected:
    typedef pointer* map_pointer;   //元素指针的指针（二维数组）

protected:
    iterator start;             //指向第一个缓冲区的第一个节点
    iterator finish;            //指向最后一个缓冲区的最后一个节点
    map_pointer map;            //一个数组，每个元素都是一个指针，指针指向一个缓冲区
    size_type map_size;         //map中指针的个数

private:
    value_type* allocate_node(){
        return data_allocator::allocate(__deque_buf_size(Bufsize, sizeof(value_type)));
    }
    void deallocate_node(value_type *p) {
        data_allocator::deallocate(p, __deque_buf_size(Bufsize, sizeof(value_type)));
    }
    size_type initial_map_size() const { return 8U;}
    size_t buffer_size() { return __deque_buf_size(Bufsize, sizeof(value_type)); }
    void fill_initialize(size_type n, const value_type& value);
    void create_map_and_nodes(size_type nums_elements);
    void create_nodes(map_pointer nstart, map_pointer nfinish);
    void destroy_nodes(map_pointer nstart, map_pointer nfinish);

    void reallocate_map(size_type nodes_to_add, bool add_at_front);

    void push_back_aux(const value_type& t);
    void push_front_aux(const value_type& t);
    void pop_back_aux();
    void pop_front_aux();
    iterator insert_aux(iterator pos, const value_type& x);
    
    void reserve_map_at_back(size_type nodes_to_add = 1){
        if(nodes_to_add + 1 > map_size - (finish.node - map)){
            reallocate_map(nodes_to_add, false);
        }
    }
    void reserve_map_at_front(size_type nodes_to_add = 1){
        if(nodes_to_add > start.node - map){
            reallocate_map(nodes_to_add, true);
        }
    }
public:
    //ctor
    //这里默认构造函数，主要是给stack和queue构造函数的时候调用的
    deque()
        :start(),finish(),map(0),map_size(0){
        create_map_and_nodes(0);
    }
    deque(int n, const value_type& value)
        :start(),finish(),map(0),map_size(0){
        fill_initialize(n, value);
    }
    iterator begin() { return start;}
    iterator end() { return finish;}
    reference operator [](size_type n){
        return start[difference_type(n)];
    }
    reference front(){ return *start;}
    reference back() { 
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }
    size_type size() const { return finish - start;}
    size_type max_size() const { return size_type(-1);}
    bool empty() const { return finish == start;}
    void clear();
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    iterator insert(iterator pos, const value_type& x);

    void push_back(const value_type& t){
        if(finish.cur != finish.last - 1){
            //当最后缓冲区存在空间时候
            construct(finish.cur, t);
            ++finish.cur;
        }
        else{
            push_back_aux(t);
        }
    }
    void push_front(const value_type& t){
        if(start.cur != start.first){
            //第一缓冲区有空间的时候
            construct(start.cur - 1, t);
            --start.cur;
        }
        else{
            push_front_aux(t);
        }
    }
    void pop_back(){
        if(finish.cur != finish.first){
            --finish.cur;
            destroy(finish.cur);
        }
        else{
            pop_back_aux();
        }
    }
    void pop_front(){
        if(start.cur != start.last - 1){
            destroy(start.cur);
            ++start.cur;
        }
        else{
            pop_front_aux();
        }
    }
    bool operator == (const deque<T>& rhs){
        return this->size() == rhs.size() && MINISTL::equal(this->start, this->finish, rhs.start);
    }
    bool operator < (const deque<T>& rhs){
        // 还没有实现deque::operator <
        // return this->size() == rhs.size() && MINISTL::equal(this->start, this->finish, rhs.start);
    }
};

template <class T, class Alloc, size_t Bufsize> 
void deque<T, Alloc, Bufsize>::create_nodes(map_pointer nstart, map_pointer nfinish) {
    map_pointer cur;
    try {
        // 为每一个节点配置空间
        for (cur = nstart; cur <= nfinish; ++cur)
            *cur = allocate_node();
    }
    catch (std::exception &) {
        destroy_nodes(nstart, cur);
        throw;
    }
}

template <class T, class Alloc, size_t Bufsize> 
void deque<T, Alloc, Bufsize>::destroy_nodes(map_pointer nstart, map_pointer nfinish) {
    for (map_pointer n = nstart; n < nfinish; ++n)
        deallocate_node(*n);
}

template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::fill_initialize(size_type n, const value_type& value){
    create_map_and_nodes(n);
    map_pointer cur;
    try
    {
        for(cur = start.node; cur < finish.node; ++cur){
            MINISTL::uninitialized_fill(*cur, *cur + buffer_size(), value);
        }
        MINISTL::uninitialized_fill(finish.first, finish.cur, value);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::create_map_and_nodes(size_type nums_elements){
    //缓存个数 = 元素个数/每个缓存的容量 + 1（如果是正好整除则多分配一个）
    size_type num_nodes = nums_elements / buffer_size() + 1;
    //map size, initial_map_size() 默认初始化mapsize = 8
    map_size = MINISTL::max(initial_map_size(), num_nodes + 2);
    map = map_allocator::allocate(map_size);

    map_pointer nstart = map + (map_size - num_nodes) / 2;
    map_pointer nfinish = nstart + num_nodes - 1;

    map_pointer cur;
    try
    {
        create_nodes(nstart, nfinish);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    start.set_node(nstart);
    finish.set_node(nfinish);
    start.cur = start.first;
    finish.cur = finish.first + nums_elements % buffer_size();
    
}

//配置一块新的缓冲区，设置新元素内容
template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::push_back_aux(const value_type& t){
    value_type t_copy = t;
    reserve_map_at_back();
    *(finish.node + 1) = allocate_node();
    try
    {
        construct(finish.cur, t_copy);
        finish.set_node(finish.node + 1);
        finish.cur = finish.first;    
    }
    catch(const std::exception& e)
    {
        deallocate_node( *(finish.node + 1));
        std::cerr << e.what() << '\n';
    }
    
}

template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::push_front_aux(const value_type& t){
    value_type t_copy = t;
    reserve_map_at_front();
    *(start.node - 1) = allocate_node();
    try
    {
        start.set_node(start.node - 1);
        start.cur = start.last - 1;
        construct(start.cur, t_copy);   
    }
    catch(const std::exception& e)
    {
        start.set_node(start.node + 1);
        start.cur = start.first;
        deallocate_node(*(start.node - 1));
        std::cerr << e.what() << '\n';
    }
    
}

//当start.cur == start.last - 1时候才会被调用
template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::pop_front_aux(){
    destroy(start.cur);
    //析构这个缓冲区
    deallocate_node(start.first);    
    //调整start指向下一个缓冲区的第一个元素
    start.set_node(start.node + 1);
    start.cur = start.first;
}

//当finish.cur == finish.first时候才会被调用
template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::pop_back_aux(){
    deallocate_node(finish.first);
    finish.set_node(finish.node - 1);
    finish.cur = finish.last - 1;
    destroy(finish.cur);
}


//重新分配map
template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::reallocate_map(size_type nodes_to_add, bool add_at_front){
    size_type old_num_nodes = finish.node - start.node + 1;
    size_type new_num_nodes = old_num_nodes + nodes_to_add;
    map_pointer new_nstart;
    if(map_size > 2*new_num_nodes){
        new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
        if(new_nstart < start.node)
        {
            MINISTL::copy(start.node, finish.node + 1, new_nstart);
        }
        else{
            MINISTL::copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
        }
    }else{
        size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
        map_pointer new_map = map_allocator::allocate(new_map_size);
        new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
        MINISTL::copy(start.node, finish.node + 1, new_nstart);
        map_allocator::deallocate(map, map_size);
        map = new_map;
        map_size = new_map_size;
    }
    start.set_node(new_nstart);
    finish.set_node(new_nstart + old_num_nodes - 1);
}

//清空deque，只留下一个缓冲区
template <typename T, typename Alloc, size_t Bufsize>
void deque<T, Alloc, Bufsize>::clear(){
    //deque在默认状态下保留一个缓冲区
    for(map_pointer node = start.node + 1; node < finish.node ; ++node){
        destroy(*node, *node + buffer_size());
        data_allocator::deallocate(*node, buffer_size());
    }
    //当还剩下头尾两个缓冲区
    if(start.node != finish.node){
        //都析构
        destroy(start.cur, start.last);
        destroy(finish.first, finish.last);
        data_allocator::deallocate(finish.first, buffer_size());
    }
    else{
        destroy(start.cur, finish.cur);
    }
    finish = start;
}

//erase一个元素,返回指向下一个元素的index
template <typename T, typename Alloc, size_t Bufsize>
typename deque<T, Alloc, Bufsize>::iterator deque<T, Alloc, Bufsize>::erase(iterator pos){
    iterator next = pos;
    ++next;
    difference_type index = pos - start;
    if(index < (size() >> 1)){
        MINISTL::copy_backward(start, pos, next);
        pop_front();
    }
    else{
        MINISTL::copy(next, finish, pos);
        pop_back();
    }
    return start + index;
}

template <typename T, typename Alloc, size_t Bufsize>
typename deque<T, Alloc, Bufsize>::iterator deque<T, Alloc, Bufsize>::erase(iterator first, iterator last){
    if(first == start && last == finish){
        clear();
        return finish;
    }
    else{
        difference_type n = last - first;
        difference_type elem_before = first - start;
        if(elem_before < (size() - n) / 2){
            MINISTL::copy_backward(start, first, last);
            iterator new_start = start + n;
            destroy(start, new_start);
            for(map_pointer cur = start.node; cur < new_start.node; ++cur){
                data_allocator::deallocate(*cur, buffer_size());
            }
            start = new_start;
        }
        else{
            copy(last, finish, first);
            iterator new_finish = finish - n;
            destroy(new_finish, finish);
            for(map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur){
                data_allocator::deallocate(*cur, buffer_size());
            }
            finish = new_finish;
        }
        return start + elem_before;
    }
}

//在指向的迭代器之前插入一个元素并设置值
template <typename T, typename Alloc, size_t Bufsize>
typename deque<T, Alloc, Bufsize>::iterator deque<T, Alloc, Bufsize>::insert(iterator pos, const value_type& x){
    if(pos.cur == start.cur){
        //如果插入的是最前端，则用push_front去做
        push_front(x);
        return start;
    }
    else if (pos.cur == finish.cur){
        //如果插入的是最尾部，则用push_back去做
        push_back(x);
        iterator tmp = finish;
        --tmp;
        return tmp;
    }
    else{
        return insert_aux(pos, x);
    }
}

template <typename T, typename Alloc, size_t Bufsize>
typename deque<T, Alloc, Bufsize>::iterator deque<T, Alloc, Bufsize>::insert_aux(iterator pos, const value_type& x){
    difference_type index = pos - start;
    value_type copy_x = x;
    if( index < size() / 2){
        push_front(front());
        iterator front1 =  start;
        ++front1;
        iterator front2 = front1;
        ++front2;
        pos = start + index;
        iterator pos1 = pos;
        ++pos1;
        MINISTL::copy(front2, pos1, front1);
    }
    else{
        push_back(back());
        iterator back1 = finish;
        --back1;
        iterator back2 = back1;
        --back2;
        pos = start + index;
        MINISTL::copy_backward(pos, back2, back1);
    }
    *pos = copy_x;
    return pos;
}

// template <typename T, typename Alloc, size_t Bufsize>
// bool operator == (const deque<T, Alloc, Bufsize>& lhs, const deque<T, Alloc, Bufsize>& rhs){
//     return lhs.size() == rhs.size() && MINISTL::equal(lhs.start, lhs.finish, rhs.start);
// }

} // namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_SEQUENCE_DEQUE_H