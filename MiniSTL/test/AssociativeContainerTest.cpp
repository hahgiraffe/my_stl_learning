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
#include "../src/Container/Associative/multiset.h"
#include "../src/Container/Associative/multimap.h"
#include "../src/Container/Associative/hashtable.h"
#include "../src/Container/Associative/hash_fun.h"

//string只测试了set<string>
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
    // myrbtree.insert_equal(88);
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
    printf("begin to test set<int>\n");
    //ctor
    MINISTL::set<int> myset;
    EXPECT_TRUE(myset.empty());
    EXPECT_EQ(myset.size(), 0);
    MINISTL::vector<int> vec;
    for(int i = 0; i < 10; ++i){
        vec.push_back(i);
    }
    MINISTL::set<int> myset_vec(vec.begin(), vec.end());
    EXPECT_FALSE(myset_vec.empty());
    EXPECT_EQ(myset_vec.size(), 10);
    // count    
    EXPECT_EQ(myset_vec.count(5), 1);
    // insert find
    myset_vec.insert(22);
    EXPECT_EQ(myset_vec.size(), 11);
    auto it = myset_vec.find(3);
    EXPECT_EQ(*it, 3);
    // *it = 4;    TODO 这里还有一个问题，就是没有搞好const_iterator，导致find出来的迭代器能赋值
    // equal_range lower_bound upper_bound
    auto res = myset_vec.equal_range(8);
    EXPECT_EQ(*res.first, 8);
    EXPECT_EQ(*res.second, 9);
    EXPECT_EQ(*myset_vec.lower_bound(6), 6);
    EXPECT_EQ(*myset_vec.upper_bound(7), 8);
    // erase
    myset_vec.erase(11);
    it = myset_vec.find(11);
    EXPECT_EQ(it, myset_vec.end());
    // clear
    myset_vec.clear();
    EXPECT_TRUE(myset_vec.empty());
    EXPECT_EQ(myset_vec.size(), 0);
    printf("begin to test set<std::string>\n");
    MINISTL::vector<std::string> vec_str;
    for(int i=0; i<100; ++i){
        vec_str.push_back(std::to_string(i));
    }
    MINISTL::set<std::string> mystrset(vec_str.begin(), vec_str.end());
    EXPECT_EQ(mystrset.size(), 100);
    EXPECT_EQ(*mystrset.begin(),"0");
    EXPECT_EQ(*mystrset.find("33"), "33");

}

TEST(AssociativeContainer, mapTest){
    printf("begin to test map<int, string>\n");
    MINISTL::map<int, std::string> mymap;
    mymap.insert({3,"123"});
    mymap[5] = "52";
    mymap[2] = "233";
    for(auto itr = mymap.begin(); itr != mymap.end(); ++itr){
        printf("%d(%s) ", itr->first, itr->second.c_str());
    }
    printf("\n");
    EXPECT_EQ(mymap.size(), 3);
    EXPECT_FALSE(mymap.empty());
    auto it = mymap.find(2);
    if(it == mymap.end()){
        printf("not found\n");
    }
    EXPECT_EQ(it->second, "233");
    mymap.erase(2);
    EXPECT_EQ(mymap.find(2), mymap.end());
}

//这里有一个bug，就是调用insert_equal的时候erase是失败的（insert_unique是正常的）
TEST(AssociativeContainer, multisetTest){
    printf("begin to test multiset<int>\n");
    //ctor
    MINISTL::multiset<int> mymultiset;
    EXPECT_TRUE(mymultiset.empty());
    EXPECT_EQ(mymultiset.size(), 0);
    mymultiset.insert(5);
    mymultiset.insert(10);
    mymultiset.insert(7);
    mymultiset.insert(7);
    // count    
    EXPECT_EQ(mymultiset.count(7), 2);
    // insert find
    mymultiset.insert(22);
    EXPECT_EQ(mymultiset.size(), 5);
    auto it = mymultiset.find(5);
    EXPECT_EQ(*it, 5);
    // equal_range lower_bound upper_bound
    auto res = mymultiset.equal_range(7);
    EXPECT_EQ(*res.first, 7);
    EXPECT_EQ(*res.second, 10);
    EXPECT_EQ(*mymultiset.lower_bound(5), 5);
    EXPECT_EQ(*mymultiset.upper_bound(7), 10);
    // erase
    // mymultiset.erase(5);
    // EXPECT_EQ(mymultiset.size(), 4);
    // EXPECT_EQ(*mymultiset.find(5), 5);
    EXPECT_EQ(mymultiset.find(11), mymultiset.end());
    // clear
    mymultiset.clear();
    EXPECT_TRUE(mymultiset.empty());
    EXPECT_EQ(mymultiset.size(), 0);

}

//这里也有erase的bug
TEST(AssociativeContainer, multimapTest){
    printf("begin to test multimap<int, string>\n");
    MINISTL::multimap<int, std::string> mymap;
    mymap.insert({3,"123"});
    mymap[5] = "52";
    mymap[2] = "233";
    mymap[2] = "sadadsf";
    for(auto itr = mymap.begin(); itr != mymap.end(); ++itr){
        printf("%d(%s) ", itr->first, itr->second.c_str());
    }
    printf("\n");
    EXPECT_EQ(mymap.size(), 4);
    EXPECT_FALSE(mymap.empty());
    auto it = mymap.find(5);
    if(it == mymap.end()){
        printf("not found\n");
    }
    EXPECT_EQ(it->second, "52");
    // mymap.erase(5);
    // EXPECT_EQ(mymap.find(5), mymap.end());
}

TEST(AssociativeContainer, hashtableTest){
    printf("begin to test hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>\n");
    MINISTL::hashtable<int, int, MINISTL::hash<int>, MINISTL::identity<int>, MINISTL::equal_to<int> >
        myht(50, MINISTL::hash<int>(), MINISTL::equal_to<int>());
    EXPECT_EQ(myht.bucket_count(), 53);
    EXPECT_EQ(myht.max_bucket_count(), 4294967291ul);
    EXPECT_EQ(myht.size(), 0);
    myht.insert_unique(59);
    myht.insert_unique(63);
    myht.insert_unique(108);
    myht.insert_unique(2);
    myht.insert_unique(53);
    myht.insert_unique(55);
    EXPECT_EQ(myht.size(), 6);
    auto ite = myht.begin();
    for(int i=0; i<myht.size(); ++i, ++ite){
        printf("%d ",*ite);
    }
    printf("\n");
    for(int i=0; i<myht.bucket_count(); ++i){
        int n = myht.elems_in_bucket(i);
        if(n){
            printf("bucket[%d] has [%d] elems.\n", i, n);
        }
    }
    //刻意把元素加到54个，让其发生rehash
    for(int i=0; i<=47; ++i){
        myht.insert_equal(i);
    }
    EXPECT_EQ(myht.size(), 54);
    EXPECT_EQ(myht.bucket_count(), 97);
    ite = myht.begin();
    for(int i=0; i<myht.size(); ++i, ++ite){
        printf("%d ",*ite);
    }
    printf("\n");
    printf("find %d\n",*(myht.find(2)));
    printf("count %d\n",myht.count(2));
    
}


int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

