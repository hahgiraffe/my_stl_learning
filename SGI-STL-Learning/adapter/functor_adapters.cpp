
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

void print(int i){
    cout<<i<<" ";
}

class Int{
public:
    explicit Int(int i):m_i(i){ }
    void print1() const {cout<<'['<<m_i<<']';}
private:
    int m_i;
};


int main(){
    ostream_iterator<int> osit(cout," ");
    int ia[]={2,21,12,7,19,23};
    vector<int> vec(ia,ia+6);
    //transform(vec.begin(),vec.end(),osit,compose1(bind2nd(multiplies<int>(),3),bind2nd(plus<int> (),2)));
    cout<<count_if(vec.begin(),vec.end(),not1(bind2nd(less<int>(),12)));//不小于12的数4
    cout<<endl;
    copy(vec.begin(),vec.end(),osit);//2 21 12 7 19 23
    cout<<endl;
    for_each(vec.begin(),vec.end(),print);//2 21 12 7 19 23
    cout<<endl;
    vector<Int> Iv;
    Iv.push_back(Int(3));
    Iv.push_back(Int(7));
    Iv.push_back(Int(20));
    Iv.push_back(Int(14));
    Iv.push_back(Int(68));
    for_each(Iv.begin(),Iv.end(),mem_fun_ref(&Int::print1));//[3][7][20][14][68]
}