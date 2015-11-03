#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "include/curses.h"
#include "binarySearchStack.h"
class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();

    bool operator == (coordinate _c){return (x==_c.x,y==_c.y);}
};

class node
{
public:
    //important coordinates
    coordinate position;
    coordinate parent;

    //integer declarations
    int gCost;
    int hCost;

    //automatic variables
    int fCost(){
        return gCost+hCost;
    }

    //constructors
    node(coordinate,coordinate, int);
    node();

    bool operator == (node _n){return (position==_n.position/*,parent==_n.parent,gCost==_n.gCost,hCost==_n.hCost*/);}
};

std::vector<coordinate> pathFinder(bool[][20], coordinate, coordinate);
std::vector<node> getNeighbors(node,bool[][20],coordinate,int);

float heuristic(coordinate,coordinate);
int getDistance(coordinate, coordinate);
bool nodeVectorContains(std::vector<node>, node);
bool nodeLibraryContains(std::vector<BST<node> > nodeLibrary, node nodeChecking);

#endif // ASTAR_H_INCLUDED
