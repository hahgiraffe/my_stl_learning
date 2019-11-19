#include "my_iterator.h"

template<typename T>
T find(T a,T b,const int& val)
{
    T temp=a;
    while(temp!=b && temp->value()!=val)
    {
        temp++;
    }
    return temp;
}

int main(int argc, char const *argv[])
{
    
    List<int> mylist;
    for(int i=0;i<5;i++)
    {
        mylist.inset_front(i);
        mylist.inset_back(i);
    }
    mylist.display();//这里还没有写好，学了list后回来填充

    ListIter<ListItem<int>> begin(mylist.front());
    ListIter<ListItem<int>> end;
    ListIter<ListItem<int>> iter;
    iter=find(begin,end,3);
    if(iter==end){
        cout<<"not find\n";
    }
    else{
        cout<<"find "<<iter->value();
    }
    iter=find(begin,end,7);
    if(iter==end){
        cout<<"not find\n";
    }
    else{
        cout<<"find "<<iter->value();
    }
    return 0;
}
