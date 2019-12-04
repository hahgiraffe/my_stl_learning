/*
 * @Author: haha_giraffe
 * @Date: 2019-11-22 16:42:50
 * @Description: file content
 */
#include "../src/Container/Sequence/vector.h"
#include "../src/Container/Sequence/list.h"
#include "../src/Container/Sequence/deque.h"
#include "../src/Container/Sequence/stack.h"
#include "../src/Container/Sequence/queue.h"
#include "../src/Container/Sequence/slist.h"
#include <algorithm>
#include "gtest/gtest.h"
#include <printf.h>

//测试vector,注意要测试每一个成员函数
TEST(ContainerTest,VectorTest){
    printf("%s\n","begin test vector");
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
    // std::cout<<"after resize"<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<std::endl;
    EXPECT_EQ(vec.size(),3);
    //vec.clear()
    vec.clear();
    EXPECT_EQ(vec.size(),0);
}

TEST(ContainerTest, ListTest){
    printf("%s\n","begin test list");
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
    // std::cout<<"mylist.size() "<<mylist.size()<<std::endl;
    //list.clear()
    mylist.clear();
    EXPECT_EQ(mylist.size(),0);

    //list.sort
    for(int i=10;i>0;--i){
        mylist.push_back(static_cast<double>(i));
    }
    mylist.sort();
    // std::cout<<"sort: ";
    // std::for_each(mylist.begin(), mylist.end(), [](double a){
    //     std::cout<<a<<" ";
    // });
    // std::cout<<std::endl;
    //list.reverse()
    // std::cout<<"after reverse: ";
    mylist.reverse();
    // std::for_each(mylist.begin(), mylist.end(), [](double a){
    //     std::cout<<a<<" ";
    // }); 
    // std::cout<<std::endl;
    //list.merge()
    MINISTL::list<double> mylist2;
    for(int i=0;i<15;i=i+2){
        mylist2.push_back(static_cast<double>(i));
    }
    mylist.reverse();
    mylist2.merge(mylist);
    // std::cout<<"after merge , mylist2 ";
    // std::for_each(mylist2.begin(), mylist2.end(), [](double a){
    //     std::cout<<a<<" ";
    // });
    // std::cout<<std::endl;
    // std::cout<<"after merge , mylist ";
    // std::for_each(mylist.begin(), mylist.end(), [](double a){
    //     std::cout<<a<<" ";
    // }); 
    // std::cout<<std::endl;
    //list.splice
    // std::cout<<"after splice ";
    mylist.push_back(100.0);
    mylist2.splice(mylist2.begin(), mylist.begin(), mylist.end());
    // std::for_each(mylist2.begin(), mylist2.end(), [](double a){
    //     std::cout<<a<<" ";
    // }); 
    // std::cout<<std::endl;

}

//deque、stack、queue都不能std::string
TEST(ContainerTest, DequeTest){
    printf("%s\n","begin test deque<int>");
    //ctor
    MINISTL::deque<int> mydeque(10,3);
    //deque.push_back() && deque.push_front()
    mydeque.push_back(200);
    mydeque.push_front(300);
    //deque.front() && deque.back()
    EXPECT_EQ(mydeque.front(), 300);
    EXPECT_EQ(mydeque.back(), 200);
    //deque.size() && deque.empty()
    EXPECT_EQ(mydeque.size(), 12);
    EXPECT_FALSE(mydeque.empty());
    //deque.pop_back() && deque.pop_front()
    mydeque.pop_back();
    mydeque.pop_front();
    EXPECT_EQ(mydeque.size(), 10);
    //deque.begin() && deque.end() && operator []
    for(auto itr = mydeque.begin(); itr != mydeque.end(); ++itr){
        *itr.cur = 66;
    }
    EXPECT_EQ(mydeque[7], 66);
    //deque.erase()
    auto eraseitr = mydeque.begin() + 2;
    mydeque.erase(eraseitr);
    EXPECT_EQ(mydeque.size(), 9);
    //deque.insert()
    auto insertitr = mydeque.end();
    mydeque.insert(insertitr, 37);
    EXPECT_EQ(mydeque.size(), 10);
    EXPECT_EQ(mydeque.back(), 37);
    //deque.clear()
    mydeque.clear();
    EXPECT_EQ(mydeque.size(), 0);
    EXPECT_TRUE(mydeque.empty());

    printf("%s\n", "begin test deque<std::string>");
    MINISTL::deque<std::string> my_string_deque;
    for(int i=0; i<10; ++i){
        my_string_deque.push_back(std::to_string(i));
    }
    for(int i=10; i<20; ++i){
        my_string_deque.push_front(std::to_string(i));
    }
    EXPECT_EQ(my_string_deque.size(), 20);
    EXPECT_EQ(my_string_deque[1], "18");
    EXPECT_EQ(my_string_deque.back(), "9");   
    EXPECT_EQ(my_string_deque.front(), "19");   
    EXPECT_FALSE(my_string_deque.empty());
    my_string_deque.pop_back();
    my_string_deque.pop_front();
    EXPECT_EQ(my_string_deque.size(), 18);
    auto insert_stritr = my_string_deque.end();
    my_string_deque.insert(insert_stritr, "chs");
    EXPECT_EQ(my_string_deque.size(), 19);
    EXPECT_EQ(my_string_deque.back(), "chs");
    //deque.clear()
    my_string_deque.clear();
    EXPECT_EQ(my_string_deque.size(), 0);
    
}

TEST(ContainerTest, StackTest){
    printf("%s\n","begin test stack");
    MINISTL::stack<int> mystack;
    MINISTL::stack<int> stack_copy;
    //stack.size()
    EXPECT_EQ(mystack.size(),0);
    //stack.push && stack.pop
    for(int i=0; i<10; ++i){
        mystack.push(i);
    }
    EXPECT_EQ(mystack.size(),10);
    EXPECT_EQ(mystack.top(),9);
    mystack.pop();
    EXPECT_EQ(mystack.top(),8);
    EXPECT_EQ(mystack.size(),9);
    EXPECT_FALSE(mystack.empty());
    EXPECT_FALSE(mystack == stack_copy);
}

TEST(ContainerTest, QueueTest){
    printf("%s\n","begin test queue");
    MINISTL::queue<double> myqueue;
    MINISTL::queue<double> myqueue_copy;
    //stack.size()
    EXPECT_EQ(myqueue.size(), 0);
    //stack.push && stack.pop
    for(int i=0; i<10; ++i){
        myqueue.push(static_cast<double>(i));
    }
    EXPECT_EQ(myqueue.size(), 10);
    EXPECT_EQ(myqueue.front(), 0);
    EXPECT_EQ(myqueue.back(), 9);
    myqueue.pop();
    EXPECT_EQ(myqueue.front(), 1);
    EXPECT_EQ(myqueue.size(), 9);
    EXPECT_FALSE(myqueue.empty());
    EXPECT_FALSE(myqueue == myqueue_copy);
}

TEST(ContainerTest, PriorityQueueTest){
    printf("%s\n","begin test priority_queue");
    MINISTL::vector<int> myvec;
    for(int i=0; i<10; ++i){
        myvec.push_back(i);
    }
    MINISTL::priority_queue<int> mypriority_queue_default;
    MINISTL::priority_queue<int> mypriority_queue(myvec.begin(), myvec.end());
    EXPECT_FALSE(mypriority_queue.empty());
    EXPECT_EQ(mypriority_queue.size(), 10);
    mypriority_queue.push(222);
    EXPECT_EQ(mypriority_queue.size(), 11);
    EXPECT_EQ(mypriority_queue.top(), 222);
    while(!mypriority_queue.empty()){
        printf("%d ",mypriority_queue.top());
        mypriority_queue.pop();
    }
    printf("\n");
    EXPECT_EQ(mypriority_queue.size(), 0);

    //这里priority_queue<string>还未完成，不知道比较的方式，functor完成后再测试
    // printf("%s\n","begin test priority_queue<string>");
    // MINISTL::priority_queue<std::string> my_str_pq;

}

TEST(ContainerTest, slistTest){
    printf("%s\n", "begin test slist");
    MINISTL::slist<int> myslist;
    EXPECT_TRUE(myslist.empty());
    EXPECT_EQ(myslist.size(), 0);
    for(int i=0; i<10; ++i){
        myslist.push_front(i);
    }
    EXPECT_EQ(myslist.size(), 10);
    auto ite = myslist.begin();
    auto ite2 = myslist.end();
    for(; ite != ite2; ++ite){
        printf("%d ", *ite);
    }
    printf("\n");
    EXPECT_EQ(myslist.front(), 9);
    myslist.pop_front();
    EXPECT_EQ(myslist.front(), 8);
    EXPECT_EQ(myslist.size(), 9);
    myslist.clear();
    EXPECT_EQ(myslist.size(), 0);
    EXPECT_TRUE(myslist.empty());

}



int main(int argc,char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
