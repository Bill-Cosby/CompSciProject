#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

struct coordinate
{
public:
    int x,y;
    coordinate(){x=0;y=0;}
    coordinate(int _x,int _y){x=_x;y=_y;}

    bool operator ==(coordinate t){return t.x==x and t.y==y;};
    bool operator !=(coordinate t){return x!=t.x and y!=t.y;}
};

struct node{
public:
    int hCost;
    int gCost;
    int fCost(){return hCost+gCost;}

    node(int,int,node*,node*);
    node(int,int);
    node(coordinate,coordinate, int);

    node(){hCost=0;gCost=0;};

    coordinate position;
    coordinate parent;

    //node operator = (const node item) {hCost=item.hCost;gCost=item.gCost;position=item.position;parent=item.parent;}
    bool operator == (node item){return item.position==position;}
    bool operator <= (node item){return fCost()<=item.fCost() or fCost()==item.fCost() and gCost<=item.gCost;}

};

int getDistance(coordinate,coordinate);

#endif // NODE_H_INCLUDED
