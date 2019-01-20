#include <iostream>
#include <memory>
using namespace std;
//先熟悉一下原提供的allocator用法
int main(int argc, char const *argv[])
{
    allocator<int> a;
    int *ptr=a.allocate(5);
    a.construct(ptr,3);
    a.construct(ptr+1,-3);
    a.construct(ptr+2,3);
    a.construct(ptr+3,-3);
    a.construct(ptr+4,3);

    for(int i=0;i<5;i++)
    {
        cout<<*(ptr+i)<<" ";
        a.destroy(ptr+i);
    }
    a.deallocate(ptr,5);

    return 0;
}
