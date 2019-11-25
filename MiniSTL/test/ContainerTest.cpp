/*
 * @Author: haha_giraffe
 * @Date: 2019-11-22 16:42:50
 * @Description: file content
 */
#include "../src/Container/Sequence/vector.h"
#include "gtest/gtest.h"

//测试vector
TEST(ContainerTest,VectorTest){
    MINISTL::vector<int> vec(3,1000);
    EXPECT_EQ(vec.size(),3);
    EXPECT_EQ(vec.capacity(),3);
    for(int i=0;i<100;++i){
        vec.push_back(i);
    }
    EXPECT_EQ(vec.size(),103);
    EXPECT_EQ(vec.back(),99);
    EXPECT_EQ(vec.front(),1000);
    EXPECT_NE(vec.capacity(),106);
}


int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
