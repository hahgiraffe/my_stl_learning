/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:19:37
 * @Description: 用于分配空间
 */
#ifndef MINI_STL_SRC_ALLOCATOR_ALLOC_H
#define MINI_STL_SRC_ALLOCATOR_ALLOC_H
#include <stdlib.h>

namespace MINISTL{

//一级分配器直接调用malloc和free
class __malloc_alloc{
    typedef void(*malloc_handler)();
public:
    static void* allocate(size_t n){
        void* res = malloc(n);
        if(res == 0) res = oom_malloc(n);
        return res;
    }
    static void deallocate(void* p, size_t n){
        free(p);
    }
    static void* reallocate(void* p, size_t old_sz, size_t new_sz){
        void* res = realloc(p,new_sz);
        if(0==res) res = oom_realloc(p,new_sz);
        return res;
    }
    //类似于set_new_handler的功能，当申请内存的时候出错，则可以自定义函数执行，然后再抛出异常
    static malloc_handler set_malloc_handler(malloc_handler f){
        malloc_handler old = malloc_alloc_oom_handle;
        malloc_alloc_oom_handle = f;
        return old;
    }
private:
    static void* oom_malloc(size_t n);
    static void* oom_realloc(void* p, size_t n);
    static void (*malloc_alloc_oom_handle) (); //定义一个函数指针对象，用于处理outofmemory的情况
};
//静态变量malloc_alloc_oom_handle初始化
void (* __malloc_alloc::malloc_alloc_oom_handle)() = 0;

void* __malloc_alloc::oom_malloc(size_t n){
    void (* my_malloc_handler)();
    void* result;
    //重复尝试释放内存然后再次申请
    for(;;){
        my_malloc_handler = malloc_alloc_oom_handle;
        if (!my_malloc_handler)
                throw std::bad_alloc();
        (*my_malloc_handler)(); //调用handler，试图释放内存
        result = malloc(n);
        if (result) return result;
    }
}

void* __malloc_alloc::oom_realloc(void* p, size_t n){
    void (* my_malloc_handler)();
    void* result;
    //重复尝试释放内存然后再次申请
    for(;;){
        my_malloc_handler = malloc_alloc_oom_handle;
        if (!my_malloc_handler)
                throw std::bad_alloc();
        (*my_malloc_handler)(); //调用handler，试图释放内存
        result = realloc(p,n);
        if (result) return result;
    }
}

#define __malloc_alloc malloc_alloc         //一级分配器
#define __ALIGN  8                          //freelist最小区块
#define __MAX_BYTES 128                     //freelist最大区块
#define __NFREELISTS  __MAX_BYTES/__ALIGN   //freelist的个数

//二级分配器
class __default_alloc{
public:
    static void* allocate(size_t n);
    static void deallocate(void* p, size_t n);
    static void* reallocate(void* p, size_t old_sz, size_t new_sz);

private:
    //freelist的节点
    union obj
    {
        union obj* free_list_link;
        char client_data[1];
    };
    
private:
    static obj* volatile free_lists[__NFREELISTS];
    //申请bytes大小的空间，用哪个freelist
    static size_t FREELIST_INDEX(size_t bytes){
        return ((bytes + __ALIGN -1)/__ALIGN -1);
    }
    //将bytes上调至8的整数倍
    static size_t ROUND_UP(size_t bytes){
        return ((bytes + __ALIGN -1) & ~(__ALIGN -1));
    }

private:
    static void* refill(size_t n);
    static char* chunk_alloc(size_t size, int& nobjs);

    static char* start_free;
    static char* end_free;
    static size_t heap_size;

};

//静态成员变量初始化
char* __default_alloc::start_free = 0;
char* __default_alloc::end_free = 0;
size_t __default_alloc::heap_size = 0;
__default_alloc::obj* volatile __default_alloc::free_lists[__NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void* __default_alloc::allocate(size_t n){

}
void __default_alloc::deallocate(void* p, size_t n){

}
void* __default_alloc::reallocate(void* p, size_t old_sz, size_t new_sz){

}

void* __default_alloc::refill(size_t n){

}
char* __default_alloc::chunk_alloc(size_t size, int& nobjs){

}

}   //MINISTL

#endif //MINI_STL_SRC_ALLOCATOR_ALLOC_H