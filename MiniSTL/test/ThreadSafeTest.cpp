/*
 * @Author: haha_giraffe
 * @Date: 2020-03-02 19:16:18
 * @Description: 并发测试
 */
#include <thread>
#include <mutex>
#include <iostream>
#include "../src/Container/Sequence/vector.h"
#include "../hahatest/hahatest.h"

MINISTL::vector<int> vec(1,1);
std::mutex mu;
MINISTL::vector_s<int> vec_s;
//当加锁以后才可以并发进行
void func1(int num){
    for(int i = 0; i < num; ++i){
        std::lock_guard<std::mutex> lock(mu);
        vec.push_back(1);
    }
    for(int i = 0; i < num; ++i){
        vec_s.push_back(1);
    }
}

void func2(int num){
    for(int i = 0; i < num; ++i){
        std::lock_guard<std::mutex> lock(mu);
        vec.push_back(1);
    }
    for(int i = 0; i < num; ++i){
        vec_s.push_back(1);
    }
}



// HAHA_TEST(VectorThreadSafeTest){
//     std::thread t1(func1, 100);
//     std::thread t2(func2, 100);
//     t1.join();
//     t2.join();
//     // for(int i = 0; i < 10; ++i){
//     //     for(int j = 0; j < 10; ++j){
//     //         printf("%d ", vec[i*10 + j]);
//     //     }
//     //     printf("\n");
//     // }
//     EXPECT_EQ(vec.size(), 201);
//     EXPECT_EQ(vec_s.size(), 200);
// }

//测试简单lock_guard的时间消耗，一千万次加锁解锁操作多消耗0.15秒
HAHA_TEST(RunTimeTest){
    MINISTL::vector<int> vec;
    MINISTL::vector_s<int> vecs;
    clock_t starttime = clock();
    for(int i = 0 ; i < 10000000; ++i){
        vec.push_back(i);
    }
    clock_t endtime = clock();
    cout << "Totle Time : " <<(double)(endtime - starttime) / CLOCKS_PER_SEC << "s" << endl;

    clock_t starttime2 = clock();
    for(int i = 0 ; i < 10000000; ++i){
        vec_s.push_back(i);
    }
    clock_t endtime2 = clock();
    cout << "Totle Time : " <<(double)(endtime2 - starttime2) / CLOCKS_PER_SEC << "s" << endl;
}

//不能复合使用
HAHA_TEST(CHECK){
    // MINISTL::vector<MINISTL::vector<int>> v;
    // for(int i = 0; i < 10; ++i)
    // {    
    //     MINISTL::vector<int> vec;
    //     vec.push_back(3);
    //     // vec.push_back(3);
    //     v.push_back(vec);
    // }
    // MINISTL::vector<int> vec;
    // vec.push_back(22);
    // v.push_back(vec);
    // cout<<v[0][0];
    // for(auto i = 0; i < v.size(); ++i){
    //     for(auto j = 0; j < v[i].size(); ++j){
    //         cout << v[i][j] << " ";
    //     }
    //     cout<<endl;
    // }

}

int main(){
    HAHATEST::run_all_test();   
}
