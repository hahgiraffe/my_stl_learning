#include "my_iterator_traits.h"
#include <list>
#include <iostream>
#include <string>
#include <vector>
//using namespace std;
static const int len=5;
template<typename T>
void _show(const T &ls)
{
    for(auto a:ls){
        std::cout<<a<<" ";
    }
    std::cout<<std::endl;
}
int main(int argc, char const *argv[])
{
    int n[len]={1,2,3,4,5};
    std::list<int> ls(n,n+len);
    std::vector<int> vec(n,n+len);
    //_show(ls);
    _show(vec);
    std::string str="hhhh";
    std::cout<<my_instance::distance(vec.begin(),vec.end(),str)<<std::endl;
    //std::cout<<str;
    return 0;
}
