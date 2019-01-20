#include "HHalloc.h"
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
    int a[5]={1,2,3,4,5};
    unsigned int i;
    vector<int,HAHA::allocator<int> >iv(a,a+5);
    for(i=0;i<iv.size();i++)
    {
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    return 0;
}
