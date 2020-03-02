/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 11:52:48
 * @Description: 测试Allocator
 */
#include <vector>
#include <list>
#include "../src/Allocator/simple_allocator.h"
#include "../src/Allocator/allocator.h"
#include "../hahatest/hahatest.h"

//测试simple_allocator
HAHA_TEST(SimpleAllocatorTest){
    std::vector<int, MINISTL::simple_allocator<int> > vec{1,2,3,4,5};
    EXPECT_EQ(vec.size(),5);
    EXPECT_EQ(vec.capacity(),5);
    EXPECT_EQ(*vec.begin(),1);
    EXPECT_EQ(*(vec.end()-1),5);
    for(int i=6;i<=106;++i){
        vec.push_back(i);
    }
    EXPECT_EQ(vec.size(),106);
    EXPECT_EQ(vec.back(),106);
    EXPECT_NE(vec.capacity(),106);
    vec.reserve(1000);
    EXPECT_EQ(vec.capacity(),1000);
}

//测试可二次分配的allocator，这个部分可能存在内存泄漏
HAHA_TEST(DoubleAllocatorTest){
    std::vector<std::string,MINISTL::allocator<std::string>> vec;
    for(int i=0;i<10;++i){
        vec.push_back(std::to_string(i));
    }
    EXPECT_EQ(vec.size(),10);
    EXPECT_EQ(vec.front(),"0");
    
}

int main(int argc,char *argv[]){
    HAHATEST::run_all_test();
}