#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <vector>
#include <iostream>
#include <stdlib.h>
class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();
};

class node
{
public:
    //important coordinates
    coordinate position;
    coordinate parent;

    //integer declarations
    int costSoFar;
    int gCost;
    int hCost;

    //automatic variables
    int fCost(){
        return this->gCost+this->hCost;
    }

    //constructors
    node(coordinate,coordinate, int);
    node();
};

std::vector<coordinate> pathFinder(bool[][20], coordinate, coordinate);
std::vector<node> getNeighbors(node,bool[][20],coordinate,int);

float heuristic(coordinate,coordinate);
int getDistance(node, node);

#endif // ASTAR_H_INCLUDED
