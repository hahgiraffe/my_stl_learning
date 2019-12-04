/*
 * @Author: haha_giraffe
 * @Date: 2019-12-04 14:48:45
 * @Description: 测试关联容器
 */
#include <stdio.h>
#include "gtest/gtest.h"
#include "../src/Container/Associative/rb_tree.h"
#include "../src/Functor/stl_function.h"

TEST(AssociativeContainer, rb_treeTest){
    //其实rb_tree只能在内部测试与使用
    printf("%s\n","begin to test rb_tree");
    MINISTL::rb_tree<int, int, MINISTL::identity<int>, MINISTL::less<int> > myrbtree;
    EXPECT_TRUE(myrbtree.empty());
    EXPECT_EQ(myrbtree.size(), 0);
    myrbtree.insert_unique(10);
    myrbtree.insert_unique(7);
    myrbtree.insert_unique(8);
    myrbtree.insert_unique(15);
    myrbtree.insert_unique(5);
    myrbtree.insert_unique(6);
    myrbtree.insert_unique(11);
    myrbtree.insert_unique(13);
    myrbtree.insert_unique(12);
    // myrbtree.insert_unique(14);
    EXPECT_FALSE(myrbtree.empty());
    EXPECT_EQ(myrbtree.size(), 9);
    auto ite = myrbtree.begin();
    auto ite2 = myrbtree.end();
    for(; ite != ite2; ++ite){
        auto rbtite = MINISTL::__rb_tree_base_iterator(ite);
        printf("%d(%d) ",*ite,rbtite.node->color);
    }
    printf("\n");

}

TEST(AssociativeContainer, setTest){

}

TEST(AssociativeContainer, mapTest){

}



int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

