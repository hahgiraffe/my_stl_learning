/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 15:19:37
 * @Description: 用于分配空间
 */
#ifndef MINI_STL_SRC_ALLOCATOR_ALLOC_H
#define MINI_STL_SRC_ALLOCATOR_ALLOC_H
#include <stdlib.h>
#include <string.h>

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

#define malloc_alloc __malloc_alloc        //一级分配器
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


/*
    调用接口，如果size > 128则调用一级分配器，否则检查freelist
*/
void* __default_alloc::allocate(size_t n){
    obj* result;
    obj* volatile *myfreelist;
    if(n > (size_t) __MAX_BYTES){
        return (malloc_alloc::allocate(n));
    }
    myfreelist = free_lists + FREELIST_INDEX(n);
    result = *myfreelist;
    if(result == 0){
        //当前没有可用的freelist，则申请
        void* r = refill(ROUND_UP(n));
        return r;
    }
    *myfreelist = result->free_list_link;
    return result;

}
/*
    调用接口，如果size > 128则调用一级分配器释放内存，否则放到对应的freelist中
*/
void __default_alloc::deallocate(void* p, size_t n){
    obj* q = (obj*)p;
    obj* volatile *myfreelist;
    if(n > __MAX_BYTES){
        malloc_alloc::deallocate(p,n);
        return;
    }
    myfreelist = free_lists + FREELIST_INDEX(n);
    q->free_list_link = *myfreelist;
    *myfreelist = q;
}
/*
    调用接口重新分配内存，记得释放p
*/
void* __default_alloc::reallocate(void* p, size_t old_sz, size_t new_sz){
    void *result;
    size_t copy_sz;

    if (old_sz > __MAX_BYTES && new_sz > __MAX_BYTES)
        return realloc(p, new_sz);
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz))
        return p;
    result = allocate(new_sz);
    copy_sz = new_sz > old_sz ? old_sz : new_sz;
    memcpy(result, p, copy_sz);
    deallocate(p, old_sz);
    return result;
}
/*
    当allocate时候发现freelist上内存不够，则重新向内存池中申请 20 * size的freelist块
*/
void* __default_alloc::refill(size_t n){
    int nobjs = 20;
    char* chunk = chunk_alloc(n,nobjs);
    obj* volatile *myfreelist;
    obj* result;
    obj* current_obj, *next_obj;
    int i;
    //如果只返回一个区块则直接返回
    if(nobjs == 1) return chunk;
    myfreelist = free_lists + FREELIST_INDEX(n);
    result = (obj*)chunk;
    //每个区块大小固定为n字节
    *myfreelist = next_obj = (obj*)(chunk + n);
    //接下就是循环分配固定大小的空间
    for(i=1; ;i++){
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj+n);
        if(nobjs - 1 == i){
            current_obj->free_list_link = 0;
            break;
        }
        else{
            current_obj->free_list_link = next_obj;
        }
    }
    return result;
}
/* 
    小块内存内存池的实现,size为一块内存的大小，nobjs默认为20
*/
char* __default_alloc::chunk_alloc(size_t size, int& nobjs){
    char* result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;  //内存剩余量
    if(bytes_left >= total_bytes){
        //当申请的内存小于内存池中的剩余量
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else if(bytes_left >= size){
        //当bytes_left < total_bytes 但是剩余量大于申请一块的内存
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else{
        //bytes_left < size
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size>>4);
        if(bytes_left > 0){
            //当bytes_left还有一点剩余,free_list中找到合适的位置，将其插入
            obj* volatile *myfreelist = free_lists + FREELIST_INDEX(bytes_left);
            ((obj*)start_free) ->free_list_link = *myfreelist;
            *myfreelist = (obj*)start_free;
        }
        //接下来malloc内存存放到内存池
        start_free = (char*)malloc(bytes_to_get);
        if(start_free == 0){
            //失败，则调用一级分配器，oom机制抛出异常
            end_free = 0;
            start_free = (char*)malloc_alloc::allocate(bytes_to_get);
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return(chunk_alloc(size,nobjs));//最后再次调用chunk_alloc取得内存
    }
}

}   //MINISTL

#endif //MINI_STL_SRC_ALLOCATOR_ALLOC_H