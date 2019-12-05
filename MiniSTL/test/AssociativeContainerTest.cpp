/*
 * @Author: haha_giraffe
 * @Date: 2019-12-04 14:48:45
 * @Description: 测试关联容器
 */
#include <stdio.h>
#include "gtest/gtest.h"
#include "../src/Container/Associative/rb_tree.h"
#include "../src/Functor/stl_function.h"
#include "../src/Container/Associative/set.h"
#include "../src/Container/Associative/map.h"
#include "../src/Container/Sequence/vector.h"

TEST(AssociativeContainer, rb_treeTest){
    //其实rb_tree只能在内部测试与使用
    printf("%s\n","begin to test rb_tree");
    MINISTL::rb_tree<int, int, MINISTL::identity<int>, MINISTL::less<int> > myrbtree;
    MINISTL::rb_tree<int, int, MINISTL::identity<int>, MINISTL::less<int> > myrbtree_copy;
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
    printf("origin rb_tree : ");
    for(; ite != ite2; ++ite){
        auto rbtite = MINISTL::__rb_tree_base_iterator(ite);
        printf("%d(%d) ",*ite,rbtite.node->color);
    }
    printf("\n");
    //增加operator=的测试
    printf("copy rb_tree : ");
    myrbtree_copy = myrbtree;
    EXPECT_FALSE(myrbtree_copy.empty());
    EXPECT_EQ(myrbtree_copy.size(), 9);
    auto ite_copy = myrbtree_copy.begin();
    auto ite2_copy = myrbtree_copy.end();
    for(; ite_copy != ite2_copy; ++ite_copy){
        auto rbtite = MINISTL::__rb_tree_base_iterator(ite_copy);
        printf("%d(%d) ",*ite_copy, rbtite.node->color);
    }
    printf("\n");
    //insert(iterator first, iterator last) 测试
    MINISTL::vector<int> vec;
    vec.push_back(100);
    vec.push_back(88);
    vec.push_back(120);
    vec.push_back(99);
    myrbtree.insert_unique(vec.begin(), vec.end());
    EXPECT_EQ(myrbtree.size(), 13);
    ite = myrbtree.begin();
    ite2 = myrbtree.end();
    printf("after insert origin rb_tree : ");
    for(; ite != ite2; ++ite){
        auto rbtite = MINISTL::__rb_tree_base_iterator(ite);
        printf("%d(%d) ",*ite,rbtite.node->color);
    }
    printf("\n");
    //find
    auto itr = myrbtree.find(12);
    EXPECT_EQ(*itr, 12);
    itr = myrbtree.find(22);
    EXPECT_EQ(itr, myrbtree.end());
    //erase
    myrbtree.erase(88);
    myrbtree.erase(myrbtree.begin());
    EXPECT_EQ(myrbtree.size(), 11);
    ite = myrbtree.begin();
    ite2 = myrbtree.end();
    printf("after erase origin rb_tree : ");
    for(; ite != ite2; ++ite){
        auto rbtite = MINISTL::__rb_tree_base_iterator(ite);
        printf("%d(%d) ",*ite,rbtite.node->color);
    }
    printf("\n");
}

TEST(AssociativeContainer, setTest){
    printf("test set\n");
}

TEST(AssociativeContainer, mapTest){
    printf("test map\n");
}



int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

