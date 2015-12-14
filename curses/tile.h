#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "node.h"

class tile : public node
{
public:
    bool corner;
    char defaultchar;
    int movementCost;
    tile(char dc,int mc){defaultchar=dc;movementCost=mc;};
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){corner=false;};
};

#endif // TILE_H_INCLUDED
