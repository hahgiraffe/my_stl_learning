#include <iostream>
using namespace std;

template<typename T>
class ListItem
{
public:
    ListItem(T val):_value(val),_next(NULL){ }
    T value() const{return _value;}
    ListItem* next() {return _next;}
    T _value;
    ListItem *_next;
};


template<typename T>
class List
{
public:
    void inset_front(T value){
    //    ListItem<T>* tmp=new ListItem<T>(value);
    //    tmp->_next=_front;
    //    _front=tmp;
    }
    void inset_back(T value){
    //    ListItem<T>* tmp=new ListItem<T>(value);
    //    _back->_next=tmp;
    //    _back=tmp;
    }
    void display() const{
    //    ListItem<T>* t=_front;
    //    while(t!=_back)
    //    {
    //        cout<<t->value()<<" ";
    //    }
    //    cout<<endl;
    }
    ListItem<T>* front() const {return _front;}
    ListItem<T>* back() const {return _back;}
private:
    ListItem<T>* _front;
    ListItem<T>* _back;
    long _size;

};

