/*
 * @Author: haha_giraffe
 * @Date: 2019-11-19 11:52:48
 * @Description: 测试Allocator
 */
#include <vector>
#include <list>
#include "../src/Allocator/simple_allocator.h"
#include "../src/Allocator/allocator.h"
#include "gtest/gtest.h"

//测试simple_allocator
TEST(AllocatorTest,SimpleAllocatorTest){
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

//测试可二次分配的allocator
TEST(AllocatorTest,DoubleAllocatorTest){
    std::list<std::string,MINISTL::allocator<std::string>> ls;
    ls.push_front("kill");
    ls.push_back("bill");
    EXPECT_EQ(ls.size(),2);
    EXPECT_EQ(ls.front(),"kill");
    
}


int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}