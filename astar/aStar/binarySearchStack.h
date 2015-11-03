#ifndef BINARYSEARCHSTACK_H_INCLUDED
#define BINARYSEARCHSTACK_H_INCLUDED

template<class T>
class BST{
public:
    T value;

    BST* Left;
    BST* Right;

    BST(T item){value = item; Left=NULL; Right=NULL;}

    void add(BST* item){
        T ww=item->value;
        bool thing;
        if (item->value.fCost() < value.fCost() or item->value.fCost() == value.fCost() and item->value.gCost < value.gCost){
            if (Left==nullptr){
                Left=item;
                Left->Left=NULL;
                Left->Right=NULL;
                return;
            }
            else if(Left!=nullptr){
                Left->add(item);
            }
        }
        else if (item->value.fCost() > value.fCost() or item->value.fCost() == value.fCost() and item->value.gCost > value.gCost){
            if (Right==nullptr){
                Right=item;
                Right->Left=NULL;
                Right->Right=NULL;
                return;
            }
            else if (Right!=nullptr){
                Right->add(item);
            }
        }
    }

    T give(){
        if (Left==nullptr)
        {
            return value;
        }
        if (Left->Left==nullptr)
        {
            return Left->value;
            if (Left->Right!=nullptr)
            {
                Left=Left->Right;
            }
        }
    }

};

#endif // BINARYSEARCHSTACK_H_INCLUDED
