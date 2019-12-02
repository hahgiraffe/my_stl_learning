/*
 * @Author: haha_giraffe
 * @Date: 2019-12-02 14:28:38
 * @Description: 测试算法
 */
#include <stdio.h>
#include "gtest/gtest.h"
#include "../src/Algorithm/heap_algorithm.h"
#include "../src/Container/Sequence/vector.h"
#include <algorithm>


TEST(AlgorithmTest, HeapTest){
    printf("%s\n","begin test heap_algorithm");
    MINISTL::vector<int> vec;
    for(int i=0; i<10; ++i){
        vec.push_back(i);
    }
    MINISTL::make_heap(vec.begin(), vec.end());
    std::for_each(vec.begin(), vec.end(), [](int a){
        printf("%d ", a);
    });
    printf("\n");
    vec.push_back(23);
    MINISTL::push_heap(vec.begin(), vec.end());
    std::for_each(vec.begin(), vec.end(), [](int a){
        printf("%d ", a);
    });
    printf("\n");
    MINISTL::pop_heap(vec.begin(), vec.end());
    printf("after pop %d\n",vec.back());
    vec.pop_back();
    MINISTL::sort_heap(vec.begin(), vec.end());
    std::for_each(vec.begin(), vec.end(), [](int a){
        printf("%d ", a);
    });
    printf("\n");
}

int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}