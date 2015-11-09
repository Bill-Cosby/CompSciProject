#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <vector>
#include <iostream>

template <class T>
class BST
{
public:
    T value;
    BST* Left;
    BST* Right;
//  constructor
    BST<T>(T item){value=item;Left=NULL;Right=NULL;}
//  functions
    void Add(BST* item)
    {
        if (item->value.fCost()<value.fCost() and Left!=NULL){
            Left->Add(item);
    }
    else if(item->value.fCost()<value.fCost() and Left==NULL){
        Left = item;
    }
    if (item->value.fCost()>value.fCost() and Right!=NULL){
        Right->Add(item);
    }
    else if(item->value.fCost()>value.fCost() and Right==NULL){
        Right = item;
    }
    }
    T Give(){
        if (Left!=NULL){
            Left->Give();
        }
        else{
            return value;
        }
    }
    bool contains(T item)
{
    if (value==item)
    {
        return true;
    }
    if (item.fCost()>value.fCost())
    {
        Right->contains(item);
    }
    else if (item.fCost()<value.fCost())
    {
        Left->contains(item);
    }
    return false;
}


};

#endif // HEAP_H_INCLUDED
