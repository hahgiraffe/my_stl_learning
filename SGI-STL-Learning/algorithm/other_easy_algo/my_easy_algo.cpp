#include "my_easy_algo.h"
#include <vector>
#include <iostream>
using namespace std;
template<typename T>
struct display{
    void operator()(const T& x) const {
        cout<<x<<" ";
    }
};

class add_to{
public:
    int operator()(){
        //x+=2;
        return x;
    }
private: static int x;
};
int add_to::x=5;

int main(){
    int ia[]={1,2,3,4,5,5,6,7,8};
    vector<int> vec(ia,ia+9);
    cout<<*my_adjacent_find(vec.begin(),vec.end())<<endl;//5
    cout<<my_count(vec.begin(),vec.end(),5)<<endl;//2
    cout<<my_count_if(vec.begin(),vec.end(),bind2nd(greater<int>(),3))<<endl;//6
    cout<<my_count_if(vec.begin(),vec.end(),bind2nd(greater_equal<int>(),3))<<endl;//7
    cout<<*my_find(vec.begin(),vec.end(),4)<<endl;//4
    vector<int> tmp{4,5};
    cout<<*my_find_first_of(vec.begin(),vec.end(),tmp.begin(),tmp.end())<<endl;//4
    my_for_each(vec.begin(),vec.end(),display<int> ());//1 2 3 4 5 5 6 7 8
    cout<<endl;
    my_generate(tmp.begin(),tmp.end(),add_to());
    my_for_each(tmp.begin(),tmp.end(),display<int> ());//5 5
    cout<<my_includes(vec.begin(),vec.end(),tmp.begin(),tmp.end())<<endl;//1
    cout<<*my_max_element(vec.begin(),vec.end())<<endl;//8
    cout<<*my_min_element(vec.begin()+1,vec.end())<<endl;//2
    vector<int> result(11);
    my_merge(vec.begin(),vec.end(),tmp.begin(),tmp.end(),result.begin());
    my_for_each(result.begin(),result.end(),display<int> ());//1 2 3 4 5 5 5 5 6 7 8
}