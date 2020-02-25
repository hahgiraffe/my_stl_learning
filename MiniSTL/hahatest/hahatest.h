/*
 * @Author: haha_giraffe
 * @Date: 2020-02-25 16:11:52
 * @Description: HaHaTest
 */
#ifndef MINISTL_HAHATEST_HAHATEST_H
#define MINISTL_HAHATEST_HAHATEST_H
#include <iostream>
#include <cstring>
#include <memory>
namespace HAHATEST{

void run_all_test();
void push_failed_msg(const std::string& test_name, const std::string& case_name, 
                    const char* file, int line, const std::string& msg);

class Test {
public:
    Test() { }
    virtual ~Test() { }
    virtual void run() = 0;
    virtual const std::string& name() = 0;
    
private:
    Test(const Test&);
    void operator=(const Test&);
};

class Case {
public:
    Case(const std::string& name) : _name(name){
        std::cout << " case " << _name << ":" << std::endl;
    }
    const std::string& name() const{
        return _name;
    }
private:
    std::string _name;
};

struct TestSaver {
    TestSaver(Test* test);
};

#define HAHA_TEST(_name_)                                                       \
    using std::cout;                                                            \
    using std::endl;                                                            \
    struct _UTest_##_name_ : public HAHATEST::Test{                             \
        _UTest_##_name_() : _name(#_name_) {}                                   \
        virtual ~_UTest_##_name_() {}                                           \
        virtual void run();                                                     \
        virtual const std::string& name() {                                     \
            return _name;                                                       \
        }                                                                       \
    private:                                                                    \
        std::string _name;                                                      \
        std::unique_ptr<HAHATEST::Case> _current_case;                          \
    };                                                                          \
    static HAHATEST::TestSaver _UT_Save_test_##_name_(new _UTest_##_name_());   \
    void _UTest_##_name_::run()                       

#define HAHA_CASE(name) _current_case.reset(new HAHATEST::Case(#name));

#define EXPECT(x)                                                               \
{                                                                               \
    if(_current_case == NULL){                                                  \
        _current_case.reset(new HAHATEST::Case("default"));                     \
    }                                                                           \
    if(x){                                                                      \
        std::cout << "EXPECT(" << #x << ") passed: ";                           \
        std::cout << std::endl;                                                 \
    } else {                                                                    \
        std::cout << "EXPECT(" << #x << ") failed: " << std::endl;              \
        std::string tmp = "EXPECT(" + std::string(#x) + ") error";                              \
        HAHATEST::push_failed_msg(_name, _current_case->name(), __FILE__, __LINE__, tmp);       \
    }                                                                                           \
}



#define EXPECT_OP(x, y, op, opname)                                             \
{                                                                               \
    if(_current_case == NULL){                                                  \
        _current_case.reset(new HAHATEST::Case("default"));                     \
    }                                                                           \
    auto _x = x;    \
    auto _y = y;    \
    if(_x op _y){   \
        std::cout << "EXPECT_" << opname << "(" << #x << ", " << #y << ") passed: ";       \
        if(strcmp("==", #op) != 0) std::cout << ": " << _x << " vs " << _y;                \
        std::cout << std::endl;                                                            \
    } else {                                                                               \
        std::cout << "EXPECT_" << opname << "(" << #x << ", " << #y << ") failed: " << _x << " vs " << _y << std::endl;     \
        std::string tmp = "EXPECT(" + std::string(#x) + ", " + std::string(#y) + ") failed";                                \
        HAHATEST::push_failed_msg(_name, _current_case->name(), __FILE__, __LINE__, tmp);                                   \
    }                                                                                                                       \
}   


#define EXPECT_EQ(x, y) EXPECT_OP(x, y, ==, "EQ")
#define EXPECT_NE(x, y) EXPECT_OP(x, y, !=, "NE")
#define EXPECT_GE(x, y) EXPECT_OP(x, y, >=, "GE")
#define EXPECT_LE(x, y) EXPECT_OP(x, y, <=, "LE")
#define EXPECT_GT(x, y) EXPECT_OP(x, y, >, "GT")
#define EXPECT_LT(x, y) EXPECT_OP(x, y, <, "LT")


}   //namespace HAHATEST

#endif
