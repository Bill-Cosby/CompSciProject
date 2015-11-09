#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include "include/curses.h"
#include "tile.h"
#include "heap.h"
class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();

    bool operator == (coordinate _c){return (x==_c.x and y==_c.y);}
};

class node
{
public:
    //important coordinates
    coordinate position;
    coordinate parent;

    //integer declarations
    int HeapIndex;
    int gCost;
    int hCost;

    //automatic variables
    int fCost(){
        return this->gCost+this->hCost;
    }

    //constructors
    node(coordinate,coordinate, int);
    node(){}

    bool operator == (node _n){return (position==_n.position/*,parent==_n.parent,gCost==_n.gCost,hCost==_n.hCost*/);}
};




std::vector<coordinate> pathFinder(std::vector<std::vector<tile> >, coordinate, coordinate);
std::vector<node> getNeighbors(node,std::vector<std::vector<tile> >,coordinate,int);

float heuristic(coordinate,coordinate);
int getDistance(coordinate, coordinate);
bool nodeVectorContains(std::vector<node>, node);

#endif // ASTAR_H_INCLUDED
