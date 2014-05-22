#include <iostream>
#include "LinkNode.h"
#ifndef LINKLIST_H
#define LINKLIST_H

template<class T>
class LinkList
{
    public:
        LinkList();
        //~LinkList();
        unsigned int listLength;
        LinkNode<T>* head;
        LinkNode<T>* tail;
        LinkNode<T>* p;
        void add(T x);
        bool deleteNode(LinkNode<T>* q);
        LinkNode<T> * findPosition (T x);
    protected:
    private:
};

template<class T>
LinkList<T>::LinkList()
{
    //ctor
    head = NULL;
    tail = NULL;
    p = NULL;
    listLength = 0;
};

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
};

template<class T>
LinkNode<T>* LinkList<T>::findPosition (T x){
    for (LinkNode<T> * p = head; p != NULL; p = p -> next){
            if ( p -> data == x)    return p;
    }
    return NULL;
};
/*template<class T>
LinkList<T>::~LinkList(){
};
*/
template<class T>
bool LinkList<T>::deleteNode(LinkNode<T>* q){
    LinkNode<T> * pre = head;
    if (q == tail){
        head = q ->next;
    }else{
        while (pre -> next != q && pre != NULL){
            pre = pre -> next;
        }
        if (pre != NULL){
             pre -> next = q -> next;
             if(q -> next == NULL)  tail = pre;
             return true;
        }else {
            return false;
        }
    }


};
#endif // LINKLIST_H
