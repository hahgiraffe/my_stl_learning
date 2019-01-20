#include "list_iterator_test.h"

template <typename Item> //指定为list服务的iterator
class ListIter
{   
public:
    Item *ptr; //相当于listItem *ptr;
    ListIter(Item *p=0):ptr(p){ } //构造函数
    
    Item& operator*() const{return *ptr;}
    Item* operator->() const {return ptr;}

    ListIter& operator++()
    {
        ptr=ptr->next();
        return *this;
    }

    ListIter operator++(int)
    {
        ListIter tmp=*this;
        (*this)++;
        return tmp;
    }

    bool operator==(const ListIter& i) const
    {
        return ptr==i.ptr;
    }

    bool operator!=(const ListIter& i) const
    {
        return ptr!=i.ptr;
    }


};