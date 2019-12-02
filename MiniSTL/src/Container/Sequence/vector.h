/*
 * @Author: haha_giraffe
 * @Date: 2019-11-22 10:46:55
 * @Description: vector实现
 */
#ifndef MINISTL_SRC_CONTAINER_SEQUENCE_VECTOR_H
#define MINISTL_SRC_CONTAINER_SEQUENCE_VECTOR_H
#include "../../Allocator/allocator.h"
#include "../../Allocator/uninitialized.h"
#include "../../Algorithm/algorithm.h"
#include "../../Iterator/stl_iterator.h"

namespace MINISTL{

template<typename T, typename Alloc = __default_alloc>
class vector{
public:
    //嵌套类型
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    //默认用二级分配器
    typedef allocator<value_type,Alloc> data_allocator; // data_allocator::allocator(n);
    iterator start;             //目前使用空间开始
    iterator finish;            //目前使用空间结尾
    iterator end_of_storage;    //目前可用空间结尾
    //新申请空间
    void insert_aux(iterator position, const T& x); 
    void deallocate(){
        if(start){
            data_allocator::deallocate(start, end_of_storage - start);
        }
    }
public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    const_iterator cbegin() const noexcept { return start; }
    const_iterator cend() const noexcept { return finish; }
    size_type size() const { return size_type(finish - start); }
    size_type capacity() const { return size_type(end_of_storage - start); }
    bool empty() const { return start ==  finish; }
    //注意这里返回引用才能更改
    reference operator[](size_type n) { return *(begin() + n); }

    //ctor dtor
    vector() : start(0), finish(0), end_of_storage(0) { }
    vector(size_type n,const T& value) { 
        fill_initialize(n, value);
    }
    template <typename InputIterator>
    vector(InputIterator begin, InputIterator end){
        size_type n = MINISTL::distance(begin, end);
        start = data_allocator::allocate(n);
        MINISTL::uninitialized_copy(begin, end, start);
        finish = end_of_storage = start + n;
    }
    vector(int n,const T& value) {
        fill_initialize(n, value);
    }
    explicit vector(size_type n){ 
        fill_initialize(n,T());
    }   //单参数要explicit
    ~vector(){
        destroy(start,finish);
        deallocate();
    }

    reference front() { return *begin(); }
    // const_reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
    void push_back(const T& x){
        if(finish != end_of_storage){
            construct(finish,x);
            ++finish;
        }
        else{
            insert_aux(end(), x);
        }
    }
    void pop_back(){
        --finish;
        destroy(finish);
    }
    iterator erase(iterator pos){
        if(pos + 1 != end()){
            //如果不是最后的一个元素，则将[pos+1,finish) copy到 [pos,finish-1)
            MINISTL::copy(pos+1, finish, pos);
        }
        //然后析构最后一个元素
        --finish;
        destroy(finish);
        return pos;
    }
    iterator erase(iterator first, iterator last){
        iterator i = MINISTL::copy(last, finish, first);
        destroy(i, finish);
        finish -= (last - first);
        return first;
    }
    //TODO
    void insert(iterator first, size_type sz, const T& value){

    }
    void resize(size_type newsize, const T& x){
        //如果resize大小小于当前大小，则把多余的删除，否则插入新增的空间
        if(newsize < size()){
            erase(begin() + newsize, end());
        }
        else{
            insert(end(), newsize - size(), x);
        }
    }
    void resize(size_type newsize){
        resize(newsize,T());
    }
    void clear(){ erase(begin(), end()); }

private:
    void fill_initialize(size_type n, const T& value){
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
    //申请内存并构造
    iterator allocate_and_fill(size_type n, const T& value){
        iterator res = data_allocator::allocate(n);
        MINISTL::uninitialized_fill_n(res,n,value);
        return res;
    }
};

template<typename T, typename Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x){
    if(finish != end_of_storage){
        construct(finish, *(finish-1));
        ++finish;
        T x_copy = x;
        //算法copy_backward，作用和copy一样，区别在于从后往前复制（这样可以在序列重叠时候拷贝）
        MINISTL::copy_backward(position, finish - 2, finish - 1);
        *position = x_copy;
    }
    else{
        //已经没有备用空间，要重新申请一个size*2的空间，再把元素copy过去
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2*old_size : 1;
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try{
            //把原数组赋值到新的位置
            new_finish = MINISTL::uninitialized_copy(start, position, new_start);
            construct(new_finish, x);
            ++new_finish;
            //将插入的元素放到新位置
            new_finish = MINISTL::uninitialized_copy(position, finish, new_finish);
        }
        catch(...){
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }
        //释放原数组
        destroy(begin(), end());
        deallocate();
        //更改指针
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

}

#endif //MINISTL_SRC_CONTAINER_SEQUENCE_VECTOR_H

