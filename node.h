#ifndef NODE_
#define NODE_
#include "myList.h"

template<class T>
class node 
{

    public:
    T data;
    node<T> * next;

        node() 
        { 
            next = nullptr;
        }
        node(T item)
        {
            data = item;
            next = nullptr;
        }
        
};
#endif

