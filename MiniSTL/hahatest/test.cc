/*
 * @Author: haha_giraffe
 * @Date: 2020-02-25 16:34:20
 * @Description: file content
 */
#include "hahatest.h"
using namespace HAHATEST;

HAHA_TEST(mytest) {
    HAHA_CASE(BASE) {
        int a = 1;
        EXPECT_EQ(a, 1);
        EXPECT_NE(a, 2);
        EXPECT_GE(a, 1);
        EXPECT_LE(a, 1);
        EXPECT_GT(a, -1);
        EXPECT_LT(a, 3);
        int b = 33;
        EXPECT_EQ(a, b);
    }

    HAHA_CASE(String) {
        std::string str1 = "abc";
        std::string str2 = "abc";
        std::string str3 = "abs";
        EXPECT_EQ(str1, str2);
        EXPECT_EQ(str1, str3);
    }
}

int main(){
    // int a  = 3, b = 4;
    // std::cout << MAX_VAL(a, b) << std::endl;
    // MIN_VAL(a, b);
    run_all_test();
}