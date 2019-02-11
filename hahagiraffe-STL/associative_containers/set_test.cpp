#include <iostream>
#include <set>
using namespace std;

int main(){
    int i=5;
    int ai[i]={5,4,6,7,6};
    set<int> s(ai,ai+i);
    cout<<"size= "<<s.size()<<endl;
    cout<<"count 6 = "<<s.count(6)<<endl;
    s.insert(5);
    cout<<"count 5 = "<<s.count(5)<<endl;
    s.erase(5);
    cout<<"after erase(5) count 5 = "<<s.count(5)<<endl;
    
    return 0;
}