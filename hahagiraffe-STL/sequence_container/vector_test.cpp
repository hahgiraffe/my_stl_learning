#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int>::iterator itr;
    cout<<typeid(itr).name()<<endl;
    //N9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE
    vector<int> vec;
    for(int i=0;i<10;i++){
        vec.push_back(i);
    }
    cout<<vec.size()<<"  "<<"  "<<vec.max_size()<<" "<<vec.capacity()<<endl;
    vector<string> vec2(10,"123");
    cout<<vec2.size()<<"  "<<"  "<<vec2.max_size()<<" "<<vec2.capacity()<<endl;
    vec2.resize(20,"1111");//注意这个resize同时改变size和capacity，源码中其实是填充
    cout<<vec2.size()<<"  "<<"  "<<vec2.max_size()<<" "<<vec2.capacity()<<endl;
    
    return 0;
}
