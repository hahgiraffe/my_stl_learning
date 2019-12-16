/*
 * @Author: haha_giraffe
 * @Date: 2019-12-02 12:46:41
 * @Description: file content
 */
#ifndef MINISTL_SRC_ALGORITHM_HEAP_ALGORITHM_H
#define MINISTL_SRC_ALGORITHM_HEAP_ALGORITHM_H
#include "../Iterator/stl_iterator.h"
#include "../Functor/stl_function.h"

namespace MINISTL{

//push_heap
template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value, const Compare& comp){
    //父节点的距离
    Distance parent = (holeIndex - 1) / 2;
    // while(holeIndex > topIndex && *(first + parent) < value ){
    while(holeIndex > topIndex && comp(*(first + parent), value) ){
        //当还没有到顶端，且父节点的值小于当前节点的值
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*, const Compare& comp){
    __push_heap(first, Distance( (last - first)-1), Distance(0), T(*(last - 1)), comp);
}

template <typename RandomAccessIterator, typename Compare = MINISTL::less< typename iterator_traits<RandomAccessIterator>::value_type > >
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last, const Compare& comp = Compare()){
    __push_heap_aux(first, last, difference_type(first), value_type(first), comp);
}

//pop_heap
template <typename RandomAccessIterator, typename T, typename Distance, typename Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value, const Compare& comp){
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;   //右子节点
    while(secondChild < len){
        if(comp(*(first + secondChild), *(first + (secondChild - 1))) ){  
            secondChild--;  //secondChild表示两个子节点中较大的一个
        }
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if(secondChild == len){
        *(first + holeIndex) = *(first + (secondChild - 1));
        holeIndex = secondChild - 1;
    }
    __push_heap(first, holeIndex, topIndex, value, comp);
}

template <typename RandomAccessIterator, typename T, typename Distance, typename Compare = MINISTL::less<typename iterator_traits<RandomAccessIterator>::value_type> >
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*, const Compare& comp = Compare()){
    *result = *first; //将最后节点值设为头部节点值
    __adjust_heap(first, Distance(0), Distance(last - first), value, comp); //调整整个堆
}

template <typename RandomAccessIterator, typename T, typename Compare>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*, const Compare& comp = Compare()){
    __pop_heap(first, last - 1, last - 1, T(*(last - 1)), difference_type(first), comp);
}

template <typename RandomAccessIterator, typename Compare = MINISTL::less< typename iterator_traits<RandomAccessIterator>::value_type > >
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last, const Compare& comp = Compare()){
    __pop_heap_aux(first, last, value_type(first), comp);
}

//sort_heap
template <typename RandomAccessIterator, typename Compare = MINISTL::less< typename iterator_traits<RandomAccessIterator>::value_type > >
void sort_heap(RandomAccessIterator first, RandomAccessIterator last, const Compare& comp = Compare()){
    //每执行一次pop_heap最大值就放在最后
    while(last - first > 1){
        pop_heap(first, last--, comp);
    }
}


//make_heap
template <typename RandomAccessIterator, typename T, typename Distance ,typename Compare>
inline void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*,const Compare& comp){
    if(last - first < 2){
        return;
    }
    Distance len = last - first;
    Distance parent = (len - 2)/2;
    while(true){
        __adjust_heap(first, parent, len, T(*(first + parent)), comp);
        if(parent == 0) return;
        parent--;
    }
}

//注意：less中元素的类型是根据iterator_traits<Iterator>::value_type萃取出来的
template<typename RandomAccessIterator, typename Compare = MINISTL::less< typename iterator_traits<RandomAccessIterator>::value_type > >
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last, const Compare& comp = Compare()){
    __make_heap(first, last, value_type(first), difference_type(first), comp);
}




}   // namespace MINISTL

#endif //MINISTL_SRC_ALGORITHM_HEAP_ALGORITHM_H
