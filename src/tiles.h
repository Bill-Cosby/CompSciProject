#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "items.h"

class tile
{
public:
    int width=10,height=10;
    int id;
    std::vector<item> itemsOnTile;
    bool occupied;
    bool impassable;

};

#endif // TILES_H_INCLUDED
