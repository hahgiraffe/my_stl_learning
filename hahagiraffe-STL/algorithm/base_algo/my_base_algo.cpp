#include "my_base_algo.h"

int main(){
    int ia[]={1,2,3,4,5};
    std::vector<int> vec(ia,ia+5);
    std::vector<int> vec2(vec);
    std::cout<<my_equal(vec.begin(),vec.end(),vec2.begin())<<std::endl;//1
    std::cout<<my_equal(vec.begin(),vec.end(),vec2.begin(),std::less<int> ())<<std::endl;//0
    my_fill(vec.begin(),vec.end(),10);
    show(vec.begin(),vec.end());//10 10 10 10 10
    my_fill_in(vec.begin(),3,2);
    show(vec.begin(),vec.end());//2 2 2 10 10
    my_iter_swap(vec.begin(),vec.end()-1);
    show(vec.begin(),vec.end());//10 2 2 10 2

    std::string a[]={"qwe","wer","ert"};
    std::string b[]={"qwe","asd","qwe"};
    std::cout<<my_lexicographical_compare(a,a+2,b,b+2); //0,a<b吗？
    std::cout<<my_lexicographical_compare(a,a+2,b,b+2,std::greater<std::string> ());  //1,a>b?

    std::cout<<my_min(vec[0],vec[1])<<std::endl;//2
    std::cout<<my_max(vec[0],vec[1])<<std::endl;//10

    std::vector<int>::iterator tmpptr1=my_mismatch(vec.begin(),vec.end(),vec2.begin()).first;//mismatch用于两个区间的第一个不匹配点，返回一个pair，first为第一个区间不匹配点的迭代器
    std::vector<int>::iterator tmpptr2=my_mismatch(vec.begin(),vec.end(),vec2.begin()).second;//second为第二个区间不匹配点的迭代器
    if(tmpptr1 != vec.end()){
        std::cout<<*tmpptr1<<std::endl;
    }else{
        std::cout<<"iv1 end"<<std::endl;//10
    }
    if(tmpptr2 != vec2.end()){
        std::cout<<*tmpptr2<<std::endl;
    }else{
        std::cout<<"iv2 end"<<std::endl;//1
    }

}