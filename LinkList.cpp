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

    if(tail == NULL)//���û��β�ڵ�������Ϊ��,node��Ϊͷ���,����β�ڵ�
    {
        head = p;
        tail = p;
    }
    else//�������ǿ�
    {
        tail -> next = p;//node��Ϊβ�ڵ����һ���ڵ�
        tail = p;//node�����β�ڵ�,��β�ڵ㸳ֵΪnode
    }
    ++listLength;//Ԫ�ظ���+1
}

template<class T>
LinkList<T>::~LinkList()
{
    //dtor
}
