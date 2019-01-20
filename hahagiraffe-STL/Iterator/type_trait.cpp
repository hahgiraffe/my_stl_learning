#include <iostream>
#include <iterator>
#include <type_traits>
using namespace std;

template <typename T>
class myclass{
public:
    myclass(int k):val(k){ }
    ~myclass()=default;

private:
    T val;
};

int main(int argc, char const *argv[])
{
    cout<<"is_abstract\t"<<is_abstract<myclass<int>>::value<<endl;
    cout<<"is_class\t"<<is_class<myclass<int>>::value<<endl;
    cout<<"is_copy_cons\t"<<is_copy_constructible<myclass<int>>::value<<endl;
    cout<<"is_copy_ass\t"<<is_copy_assignable<myclass<int>>::value<<endl;
    cout<<"is_default_constructible\t"<<is_default_constructible<myclass<int>>::value<<endl;
    cout<<"is_trivially_constructible\t"<<is_trivially_constructible<myclass<int>>::value<<endl;
    return 0;
}
