#include <iostream>
using namespace std;

struct A{

};
struct B:public A{

};
struct C:public A{

};

template <typename T>
void func(T& p ,A){
    cout<<"A version\n";
}

template <typename T>
void func(T& p,C){
    cout<<"C version\n";
}


int main(int argc, char const *argv[])
{
    int *p;
    func(p,A()); //A()相当于创建了一个A类的临时对象，忽略了对象名
    func(p,B()); //当没有参数完全符合时候，因继承关系自动传递调用父类
    func(p,C()); //有完全符合的参数，即不会调用父类
    return 0;
}
