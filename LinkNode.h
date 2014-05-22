#ifndef LINKNODE_H
#define LINKNODE_H
#include <iostream>
using namespace std;

template<class T>
class LinkNode
{
public:
    LinkNode(){  next = NULL;    }
    ~LinkNode(){};
    T data;
    LinkNode* next;
    T getData(){    return data; };
};

#endif // LINKNODE_H
