/*
 * @Author: haha_giraffe
 * @Date: 2019-12-02 14:28:38
 * @Description: 测试算法
 */
#include <stdio.h>
#include "../hahatest/hahatest.h" 
#include "../src/Algorithm/heap_algorithm.h"
#include "../src/Container/Sequence/vector.h"
#include "../src/Algorithm/numeric_algo.h"
#include "../src/Functor/stl_function.h"
#include "../src/Algorithm/stl_algo.h"
#include <iostream>
#include <iterator>


HAHA_TEST(HeapTest){
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

HAHA_TEST(NumericTest){
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

template <typename T>
struct display{
    void operator()(const T& x) const{
        std::cout<<x<<" ";
    }
};

class even_by_two{
public:
    int operator()() const{
        return _x += 2;
    }
private:
    static int _x;
};
int even_by_two::_x = 0;

HAHA_TEST(BaseAlgo){
    printf("begin test basealgo\n");
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8};
    MINISTL::vector<int> myvec{ia, ia+sizeof(ia)/sizeof(int)};
    EXPECT_EQ(*MINISTL::adjacent_find(myvec.begin(), myvec.end()), 6);
    EXPECT_EQ(*MINISTL::adjacent_find(myvec.begin(), myvec.end(), MINISTL::equal_to<int>()), 6);
    EXPECT_EQ(MINISTL::count(myvec.begin(), myvec.end(), 6), 3);
    // EXPECT_EQ(MINISTL::count_if(myvec.begin(), myvec.end(), MINISTL::bind2nd(less<int>(), 7)), 6);
    EXPECT_EQ(*MINISTL::find(myvec.begin(), myvec.end(), 4), 4);
    // EXPECT_EQ(*MINISTL::find_if(myvec.begin(), myvec.end(), MINISTL::bind2nd(greater<int>(), 2)), 3);
    MINISTL::vector<int> iv2{ia+6, ia+8};
    // std::cout<<iv2[0]<<" "<<iv2[1];
    // EXPECT_EQ(*(MINISTL::find_end(myvec.begin(), myvec.end(), iv2.begin(), iv2.end()) + 3), 8);
    EXPECT_EQ(*(MINISTL::find_first_of(myvec.begin(), myvec.end(), iv2.begin(), iv2.end()) + 3), 7);
    MINISTL::for_each(myvec.begin(), myvec.end(), display<int>());std::cout<<std::endl;
    MINISTL::generate(iv2.begin(), iv2.end(), even_by_two());
    MINISTL::for_each(iv2.begin(), iv2.end(), display<int>());std::cout<<std::endl;
    MINISTL::remove(myvec.begin(), myvec.end(), 6);
    MINISTL::for_each(myvec.begin(), myvec.end(), display<int>());std::cout<<std::endl;
    
}

HAHA_TEST(ExtendAlgo){
    printf("begin test extendalgo\n");
    int ia[] = {1,2,3,33,794,5,109,3123,44};
    MINISTL::vector<int> myvec{ia, ia+9};
    MINISTL::random_shuffle(myvec.begin(), myvec.end());
    MINISTL::for_each(myvec.begin(), myvec.end(), display<int>());std::cout<<std::endl;
    MINISTL::partial_sort(myvec.begin(), myvec.begin() + 5, myvec.end());   //保证前五个数是最小的五个数且从小到大排序
    MINISTL::for_each(myvec.begin(), myvec.end(), display<int>());std::cout<<std::endl;
    MINISTL::sort(myvec.begin(), myvec.end());   
    MINISTL::for_each(myvec.begin(), myvec.end(), display<int>());std::cout<<std::endl;
    // MINISTL::vector<int> testsort;
    // for(int i=100; i>0; --i){
    //     testsort.push_back(i);
    // }
    // MINISTL::sort(testsort.begin(), testsort.end());   
    // MINISTL::for_each(testsort.begin(), testsort.end(), display<int>());std::cout<<std::endl;

}

int main(int argc,char *argv[]){
    HAHATEST::run_all_test();
}