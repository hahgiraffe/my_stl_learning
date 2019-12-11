/*
 * @Author: haha_giraffe
 * @Date: 2019-12-10 10:18:42
 * @Description: hash函数（仿函数，用于确定hashtable的bucket位置）
 */
#ifndef MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHFUNC_H
#define MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHFUNC_H
#include <stdlib.h>

namespace MINISTL{

//目前无法处理float，string，double等类型，如果需要处理就需要自己定义偏特化hash

template <typename Key>
struct hash{ };
inline size_t __stl_hash_string(const char* s){
    unsigned long h = 0;
    for(; *s; ++s){
        h = 5*h + *s;
    }
    return size_t(h);
}

//偏特化
template <>
struct hash<char*>{
    size_t operator()(const char* s) const {
        return __stl_hash_string(s);
    }
};

template <>
struct hash<const char*>{
    size_t operator()(const char* s) const {
        return __stl_hash_string(s);
    }
};

template <>
struct hash<char>{
    size_t operator()(char s) const {
        return s;
    }
};

template <>
struct hash<unsigned char>{
    size_t operator()(unsigned char s) const {
        return s;
    }
};

template <>
struct hash<signed char>{
    size_t operator()(signed char s) const {
        return s;
    }
};

template <>
struct hash<short>{
    size_t operator()(short s) const {
        return s;
    }
};

template <>
struct hash<unsigned short>{
    size_t operator()(unsigned short s) const {
        return s;
    }
};

template <>
struct hash<int>{
    size_t operator()(int s) const {
        return s;
    }
};

template <>
struct hash<unsigned int>{
    size_t operator()(unsigned int s) const {
        return s;
    }
};

template <>
struct hash<unsigned long>{
    size_t operator()(unsigned long s) const {
        return s;
    }
};

template <>
struct hash <long>{
    size_t operator()(long s) const {
        return s;
    }
};


}   //namespace MINISTL

#endif //MINISTL_SRC_CONTAINER_ASSOCIATIVE_HASHFUNC_H
