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
    coordinate position;
    coordinate parent;
    int costSoFar;
    int gCost;
    int hCost;
    int fCost;
    node(coordinate,coordinate, int);
    node();
};

float heuristic(coordinate,coordinate);

std::vector<coordinate> pathFinder(bool[][20], coordinate, coordinate);
#endif // ASTAR_H_INCLUDED
