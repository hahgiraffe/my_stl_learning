/*
 * @Author: haha_giraffe
 * @Date: 2019-12-02 14:28:38
 * @Description: 测试算法
 */
#include <stdio.h>
#include "gtest/gtest.h"
#include "../src/Algorithm/heap_algorithm.h"
#include "../src/Container/Sequence/vector.h"
#include "../src/Algorithm/numeric_algo.h"
#include "../src/Functor/stl_function.h"
#include <iostream>


TEST(AlgorithmTest, HeapTest){
    printf("%s\n","begin test heap_algorithm");
    MINISTL::vector<int> vec;
    for(int i=0; i<10; ++i){
        vec.push_back(i);
    }
    MINISTL::make_heap(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); ++it){
        printf("%d ", *it);
    }
    printf("\n");
    vec.push_back(23);
    MINISTL::push_heap(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); ++it){
        printf("%d ", *it);
    }
    printf("\n");
    MINISTL::pop_heap(vec.begin(), vec.end());
    printf("after pop %d\n",vec.back());
    vec.pop_back();
    MINISTL::sort_heap(vec.begin(), vec.end());
    for(auto it = vec.begin(); it != vec.end(); ++it){
        printf("%d ", *it);
    }
    printf("\n");
}

TEST(AlgorithmTest, NumericTest){
    printf("begin test Numeric\n");
    int ia[5] = {1,2,3,4,5};
    MINISTL::vector<int> myvec(ia, ia+5);
    EXPECT_EQ(MINISTL::accumulate(myvec.begin(), myvec.end(), 0), 15);
    EXPECT_EQ(MINISTL::accumulate(myvec.begin(), myvec.end(), 0, MINISTL::minus<int>()), -15);
    EXPECT_EQ(MINISTL::inner_product(myvec.begin(), myvec.end(), myvec.begin(), 10), 65);
    EXPECT_EQ(MINISTL::inner_product(myvec.begin(), myvec.end(), myvec.begin(), 10, MINISTL::minus<int>(), MINISTL::plus<int>()), -20);
    std::ostream_iterator<int> oite(std::cout, " ");
    MINISTL::partial_sum(myvec.begin(), myvec.end(), oite);
    printf("\n");
    MINISTL::partial_sum(myvec.begin(), myvec.end(), oite, MINISTL::minus<int>());
    printf("\n");
    MINISTL::adjacent_difference(myvec.begin(), myvec.end(), oite);
    printf("\n");
    MINISTL::adjacent_difference(myvec.begin(), myvec.end(), oite, MINISTL::plus<int>());
    printf("\n");

}

TEST(AlgorithmTest, BaseAlgo){
    printf("begin test basealgo\n");
    int ia[] = {1,2,3,33,794,5,109,3123,44};
    MINISTL::vector<int> myvec{ia, ia+5};
    
}

int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}