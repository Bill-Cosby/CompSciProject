#ifndef SPRING_H_INCLUDED
#define SPRING_H_INCLUDED
#include "node.h"

class spring
{
    public:
    int x0;
    int y0;
    std::vector<coordinate> wetTiles;
    spring(int x, int y){x0=x; y0=y; coordinate E(x0,y0); wetTiles.push_back(E);}
};

#endif // SPRING_H_INCLUDED
