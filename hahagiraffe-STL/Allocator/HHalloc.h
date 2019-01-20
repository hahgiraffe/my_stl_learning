//my_initl_alloc
#ifndef _HAHA_ALLOC_
#define _HAHA_ALLOC_
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

// size_t是unsigned类型，用于指明数组长度或下标，它必须是一个正数，std::size_t.设计size_t就是为了适应多个平台，其引入增强了程序在不同平台上的可移植性。
// ptrdiff_t是signed类型，用于存放同一数组中两个指针之间的差距，它可以使负数，std::ptrdiff_t.同上，使用ptrdiff_t来得到独立于平台的地址差值.
// size_type是unsigned类型,表示容器中元素长度或者下标，vector<int>::size_type i = 0;
// difference_type是signed类型,表示迭代器差距，vector<int>:: difference_type = iter1-iter2.


namespace HAHA{
    template <typename T>
    inline T* _allocate(ptrdiff_t size,T*){
        std::set_new_handler(0);
        T* tmp=(T*)(::operator new((size_t) (size*sizeof(T))));//调用全局operator::new()分配一个空间，大小为size*sizeof(T),返回头指针tmp
        if(tmp==0)
        {
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }
    template <typename T>
    inline void _deallocate(T* buffer){
        ::operator delete(buffer);
    }

    template <typename T1,typename T2>
    inline void _construct(T1* p,const T2& value){//构造对象
        new(p) T1(value);
    }

    template <typename T>
    inline void _destroy(T* ptr){//析构对象
        ptr->~T();
    }

    template <typename T>
    class allocator{
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        //嵌套,这个的作用是什么？？？
        template <typename U>
        struct rebind{
            typedef allocator<U> other;
        };

        pointer allocate(size_type n, const void* hint=0){
            return _allocate((difference_type)n,(pointer)0);
        }

        void deallocate(pointer p,const T& value){
            _deallocate(p);
        }
        void construct(pointer p,const T& value){
            _construct(p,value);
        }
        void destroy(pointer p,const T& value){
            _destroy(p);
        }
        pointer address(reference x){
            return (pointer)&x;
        }
        const_pointer const_address(const_reference x){
            return(const_pointer)&x;
        }

        size_type max_size() const{
            return size_type(UINT_MAX/sizeof(T));
        }

    };
}

#endif //_HAHA_ALLOC_