#ifndef PATHFINDER_H_INCLUDED
#define PATHFINDER_H_INCLUDED
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <iostream>
#include "include/curses.h"

class coordinate
{
public:
    int x,y;
    coordinate(){x=0;y=0;}
    coordinate(int _x,int _y){x=_x;y=_y;}

    bool operator ==(coordinate t){return t.x==x and t.y==y;};
    bool operator !=(coordinate t){return x!=t.x and y!=t.y;}
};

class node{
public:
    node* Left;
    node* Right;
    int hCost;
    int gCost;
    int fCost(){return hCost+gCost;}

    node(int,int,node*,node*);
    node(int,int);
    node(coordinate,coordinate, int);

    node(){hCost=0;gCost=0;Left=NULL;Right=NULL;};

    coordinate position;
    coordinate parent;

    //node operator = (const node item) {hCost=item.hCost;gCost=item.gCost;position=item.position;parent=item.parent;}
    bool operator == (node item){return item.position==position;}
    bool operator <= (node item){return fCost()<=item.fCost() or fCost()==item.fCost() and gCost<=item.gCost;}

};

std::vector<node> findNeighbors(std::vector<std::vector<bool> >, node, coordinate);
std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > ,coordinate,coordinate);
int manhattanDistance(coordinate,coordinate);
bool vectorContains(coordinate, std::vector<node>);

#endif // PATHFINDER_H_INCLUDED
