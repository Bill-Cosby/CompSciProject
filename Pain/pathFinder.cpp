#include "pathFinder.h"

node::node(int h,int g)
{
    hCost=h;
    gCost=g;
    Left=NULL;
    Right=NULL;
}

node::node(int h, int g, node* L, node* R)
{
    hCost=h;
    gCost=g;
    Left=L;
    Right=R;
}

bool node::contains(node item)
{
    if (item<=*this)
    {
        if (item==*this)
        {
            return true;
        }
        if (Left){
           Left->contains(item);
        }
    }
    if (Right){
        Right->contains(item);
    }
    return false;
}

void node::add(node* item)
{
    if (*item<=*this){
        if (Left!=NULL){
            Left->add(item);
        }else{
            Left=item;
        }
        return;
    }
    if (Right!=NULL){
        Right->add(item);
    }else{
        Right=item;
    }
    return;
}

node node::give()
{
    if (Left->Left==NULL){
        node temp=*Left;
        if (Left->Right!=NULL){
            Left=Left->Right;
        }else{
            Left=NULL;
        }
        return temp;
    }
}

std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > _map, coordinate start, coordinate goal){

    std::vector<node> openSet;
    std::vector<node> closedSet;
    std::vector<node> neighborSet;



    while (openSet.size()!=0){

    }

}
