/*
 * @Author: haha_giraffe
 * @Date: 2019-11-22 16:42:50
 * @Description: file content
 */
#include "../src/Container/Sequence/vector.h"
#include "../src/Container/Sequence/list.h"
#include <algorithm>
#include "gtest/gtest.h"
#include <iostream>

//测试vector,注意要测试每一个成员函数
TEST(ContainerTest,VectorTest){
    //vector构造函数
    MINISTL::vector<int> vec(3,1000);
    //vec.empty()
    EXPECT_FALSE(vec.empty());
    //vec.size()
    EXPECT_EQ(vec.size(),3);
    //vec.capacity()
    EXPECT_EQ(vec.capacity(),3);
    //operator []
    EXPECT_EQ(vec[2],1000);
    //vec.push_back
    for(int i=0;i<100;++i){
        vec.push_back(i);
    }
    EXPECT_EQ(vec.size(),103);
    //vec.back()
    EXPECT_EQ(vec.back(),99);
    //vec.pop_back()
    vec.pop_back();
    EXPECT_EQ(vec.size(),102);
    //vec.front()
    EXPECT_EQ(vec.front(),1000);
    EXPECT_NE(vec.capacity(),106);
    //vec.erase()
    for(int i=0;i<3;++i){
        vec.erase(vec.begin());
    }
    EXPECT_EQ(vec.size(),99);
    //vec.resize()
    vec.resize(3);
    std::cout<<"after resize"<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<std::endl;
    EXPECT_EQ(vec.size(),3);
    //vec.clear()
    vec.clear();
    EXPECT_EQ(vec.size(),0);
}

TEST(ContainerTest, ListTest){
    //ctor
    MINISTL::list<double> mylist;
    //list.empty()
    EXPECT_TRUE(mylist.empty());
    //list.push_back() && list.push_front()
    for(int i=0;i<500;++i){
        mylist.push_back(static_cast<double>(i));
    }
    for(int i=500;i<1000;++i){
        mylist.push_front(static_cast<double>(i));
    }
    EXPECT_FALSE(mylist.empty());
    //list.size()
    EXPECT_EQ(mylist.size(),1000);
    //list.front() && list.back()
    EXPECT_EQ(mylist.front(),999);
    EXPECT_EQ(mylist.back(),499);
    //list.pop_back() && list.pop_front()
    for(int i=0;i<10;++i){
        mylist.pop_back();
        mylist.pop_front();
    }
    EXPECT_EQ(mylist.size(),980);
    //list.remove()
    mylist.remove(33);
    EXPECT_EQ(mylist.size(),979);
    //list.unique()
    EXPECT_EQ(mylist.back(),489);
    mylist.push_back(489.0);
    mylist.unique();
    EXPECT_EQ(mylist.size(),979);
    //list.erase()
    EXPECT_EQ(mylist.front(), 989);
    mylist.erase(mylist.begin()++);
    EXPECT_EQ(mylist.front(), 988);
    EXPECT_EQ(mylist.size(),978);
    std::cout<<"mylist.size() "<<mylist.size()<<std::endl;
    //list.clear()
    mylist.clear();
    EXPECT_EQ(mylist.size(),0);

    //list.sort
    for(int i=10;i>0;--i){
        mylist.push_back(static_cast<double>(i));
    }
    mylist.sort();
    std::cout<<"sort: ";
    std::for_each(mylist.begin(), mylist.end(), [](double a){
        std::cout<<a<<" ";
    });
    std::cout<<std::endl;
    //list.reverse()
    std::cout<<"after reverse: ";
    mylist.reverse();
    std::for_each(mylist.begin(), mylist.end(), [](double a){
        std::cout<<a<<" ";
    }); 
    std::cout<<std::endl;
    //list.merge()
    MINISTL::list<double> mylist2;
    for(int i=0;i<15;i=i+2){
        mylist2.push_back(static_cast<double>(i));
    }
    mylist.reverse();
    mylist2.merge(mylist);
    std::cout<<"after merge , mylist2 ";
    std::for_each(mylist2.begin(), mylist2.end(), [](double a){
        std::cout<<a<<" ";
    }); 
    std::cout<<std::endl;
    std::cout<<"after merge , mylist ";
    std::for_each(mylist.begin(), mylist.end(), [](double a){
        std::cout<<a<<" ";
    }); 
    std::cout<<std::endl;
    //list.splice
    std::cout<<"after splice ";
    mylist.push_back(100.0);
    mylist2.splice(mylist2.begin(), mylist.begin(), mylist.end());
    std::for_each(mylist2.begin(), mylist2.end(), [](double a){
        std::cout<<a<<" ";
    }); 
    std::cout<<std::endl;

}

int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
