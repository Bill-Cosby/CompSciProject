#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <vector>
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
    int gCost;
    int hCost;
    int fCost;
    node(coordinate,coordinate,coordinate, int);
};

float heuristic(coordinate,coordinate);

std::vector<coordinate> pathFinder(bool, coordinate, coordinate);
#endif // ASTAR_H_INCLUDED
