#include "my_algo.h"
#include <iterator>
int main(){
    std::vector<int> vec{1,3,4,5};
    std::vector<int>::iterator itr = my_find(vec.begin(),vec.end(),3);
    if(itr==vec.end()){
        std::cout<<"not found\n";
    }
    else{
        std::cout<<*itr<<std::endl;//3
    }
    
    std::cout<<"accumulate---------\n";
    int sum=my_accumulate(vec.begin()+1,vec.end(),0);//v1
    std::cout<<sum<<std::endl;//12
    sum=my_accumulate(vec.begin(),vec.end(),100,my_minus<int> ());
    std::cout<<sum<<std::endl;//100-1-3-4-5=87
    sum=my_accumulate(vec.begin(),vec.end(),1,my_multiply<int> ());
    std::cout<<sum<<std::endl;//1*1*3*4*5=60

    std::cout<<"adjacent_difference---------\n";
    std::ostream_iterator<int> oite(std::cout," ");
    my_adjacent_difference(vec.begin(),vec.end(),oite);//1 2 1 1
    my_adjacent_difference(vec.begin(),vec.end(),oite,my_plus<int> ()); //1 4 7 9
    
    std::cout<<"inner_profuct---------\n";
    int tmp=my_inner_product(vec.begin(),vec.end(),vec.begin(),0);
    std::cout<<tmp<<std::endl;//51=1*1+3*3+4*4+5*5
    tmp=my_inner_product(vec.begin(),vec.end(),vec.begin(),0,my_minus<int> (),my_multiply<int> ());//-51=0-1*1-3*3-4*4-5*5
    std::cout<<tmp<<std::endl;
    //power
    std::cout<<"inner_profuct---------\n";
    tmp=my_power(3,5);
    std::cout<<tmp<<std::endl;
}
