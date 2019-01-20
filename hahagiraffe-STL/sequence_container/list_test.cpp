#include <list>
#include <iostream>
using namespace std;
template <typename T>
void printlist(const list<T> &ls){
    for(auto a: ls){
        cout<<a<<" ";
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    cout<<"测试构造函数"<<endl;
    list<int> ls{1,2,3,4,5,6};
    printlist(ls);
    list<int> ls2(ls.begin(),ls.end());
    printlist(ls2);
    list<int> ls3(ls);
    printlist(ls3);
    cout<<"测试元素操作"<<endl;
    
    ls.push_front(9);
    printlist(ls);
    
    ls.push_back(9);
    printlist(ls);
    
    list<int>::iterator itr=ls.begin();
    ls.erase(itr);
    printlist(ls);

    ls.pop_front();
    printlist(ls);

    ls.pop_back();
    printlist(ls);

    ls.remove(4);
    printlist(ls);

    ls.reverse();
    printlist(ls);
    
    ls.sort();
    printlist(ls);
    
    ls2.sort();
    ls.merge(ls2);
    printlist(ls);

    ls.splice(ls.begin(),ls3);
    printlist(ls3);
    printlist(ls);
    return 0;

}
