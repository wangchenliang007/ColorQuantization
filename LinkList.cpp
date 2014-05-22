#include "LinkList.h"
#include <iostream>

template<class T>
LinkList<T>::LinkList()
{
    //ctor
    head = NULL;
    tail = NULL;
    p = NULL;
    listLength = 0;
}

template<class T>
void  LinkList<T>::add(T x){
    p =new LinkNode<T>();
    p -> data= x;
    p -> next = NULL;

    if(tail == NULL)//如果没有尾节点则链表为空,node既为头结点,又是尾节点
    {
        head = p;
        tail = p;
    }
    else//如果链表非空
    {
        tail -> next = p;//node既为尾节点的下一个节点
        tail = p;//node变成了尾节点,把尾节点赋值为node
    }
    ++listLength;//元素个数+1
}

template<class T>
LinkList<T>::~LinkList()
{
    //dtor
}
