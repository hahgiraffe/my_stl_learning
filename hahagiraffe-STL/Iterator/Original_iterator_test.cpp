#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <typeinfo>
using namespace std;
int main(int argc, char const *argv[])
{
    const int len=7;
    int a[len]={1,3,5,6,8,11,13};
    vector<int> vec(a,a+len);
    list<int> ls(a,a+len);
    vector<int>::iterator itr=find(vec.begin(),vec.end(),13);
    if(itr==vec.end()){
        cout<<"not find\n";
    }
    else{
        cout<<"find "<<*itr<<endl;
    }
    auto i=ls.begin();
    for(;i!=ls.end();i++){
        cout<<*i<<" ";
    }
    cout<<typeid(i).name()<<endl;

    return 0;
}
