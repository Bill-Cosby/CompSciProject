#ifndef PATHFINDER_H_INCLUDED
#define PATHFINDER_H_INCLUDED

class coordinate
{
public:
    int x,y;
    coordinate(){x=0;y=0;}
    coordinate(int _x,int _y){x=_x;y=_y;}

    bool operator ==(coordinate t){return t.x==x and t.y==y;};
};

class node{
private:
    node* Left;
    node* Right;
public:
    int hCost;
    int gCost;
    int fCost(){return hCost+gCost;}

    coordinate position;
    coordinate parent;

    bool operator == (node item){return item.position==position;}
    bool operator <= (node item){return fCost()<=item.fCost() or fCost()==item.gCost and fCost()<=item.gCost;}
};

std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > ;coordinate;coordinate);

#endif // PATHFINDER_H_INCLUDED
