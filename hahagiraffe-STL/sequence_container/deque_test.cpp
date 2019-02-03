#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
void printdeque(const deque<T> &ls){
    for(auto a: ls){
        cout<<a<<" ";
    }
    cout<<endl;
}
int main()
{
    deque<int> mydeque;
    for(int i=1;i<10;i++){
        mydeque.push_front(i);
    }
    printdeque(mydeque); //9 8 7 6 5 4 3 2 1
    
}