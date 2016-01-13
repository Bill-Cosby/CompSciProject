#ifndef BINARYSEARCHSTACK_H_INCLUDED
#define BINARYSEARCHSTACK_H_INCLUDED

template<class T>
class BST{
public:
    T value;

    BST* Left;
    BST* Right;
    //int DDS;

    BST(T item){value = item; Left=NULL; Right=NULL;}

    int add(T item){
        T ww=item;
        T www=value;
        bool thing;
        if (item.fCost() < value.fCost() or item.fCost() == value.fCost() and item.gCost < value.gCost){
            if (Left==nullptr){
                return value.DDS;
            }
            else if(Left!=nullptr){
                Left->add(item);
            }
        }
        else if (item.fCost() > value.fCost() or item.fCost() == value.fCost() and item.gCost > value.gCost){
            if (Right==nullptr){
                return value.DDS;
            }
            else if (Right!=nullptr){
                Right->add(item);
            }
        }
    }

    void setNode(BST* item)
    {
        if (item->value.fCost() < value.fCost() or item->value.fCost() == value.fCost() and item->value.gCost < value.gCost){
            Left=item;
        }
        if (item->value.fCost() > value.fCost() or item->value.fCost() == value.fCost() and item->value.gCost > value.gCost){
            Right=item;
        }
    }

    int give(){
        if (Left==nullptr)
        {
            return value.DDS;
        }
        if (Left->Left==nullptr)
        {
            return Left->value.DDS;
            if (Left->Right!=nullptr)
            {
                Left=Left->Right;
            }
        }
    }

};

#endif // BINARYSEARCHSTACK_H_INCLUDED
