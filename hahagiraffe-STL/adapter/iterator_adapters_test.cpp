#include <iterator>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;
/*适配器（配接器）三种
1. 应用于容器 container adapter :queue,stack
2. 应用于迭代器 insert iterator(back_inserter,front_inserter,inserter)
              reverse iterator
              iostream iterator(istream_iterator,ostream_iterator)
3.应用于仿函数 functor adapter
*/

int main(){
    ostream_iterator<int> outite(cout," ");
    int ia[]={0,1,2,3,4,5};
    deque<int> id(ia,ia+6);
    copy(id.begin(),id.end(),outite);//0 1 2 3 4 5
    cout<<endl;
    
    copy(ia+1,ia+2,front_inserter(id));
    copy(id.begin(),id.end(),outite);//1 0 1 2 3 4 5
    cout<<endl;

    copy(ia+3,ia+4,back_inserter(id));//1 0 1 2 3 4 5 3
    copy(id.begin(),id.end(),outite);
    cout<<endl;

    deque<int>::iterator ite=find(id.begin(),id.end(),5);
    copy(ia+0,ia+3,inserter(id,ite));
    copy(id.begin(),id.end(),outite);//1 0 1 2 3 4 0 1 2 5 3
    cout<<endl;

    istream_iterator<int> inite(cin),eos;
    copy(inite,eos,inserter(id,id.begin()));//在id.begin()前面加输入的
    copy(id.begin(),id.end(),outite);//12 3 55 1 0 1 2 3 4 0 1 2 5 3
}