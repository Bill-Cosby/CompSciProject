#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"

class tile : public node
{
public:
    bool isDoor;
    char defaultchar;
    int movementCost;
    tile(char dc,int mc){defaultchar=dc;movementCost=mc;};
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;};

    virtual char drawTile(){return defaultchar;}
    virtual bool interactWithDoor(bool opening){};
};

class door : public tile
{
public:
    bool open;
    char openSymbol;
    char closedSymbol;
    door(bool _o);
    virtual char drawTile(){if (open==true){return openSymbol;}else{return closedSymbol;}}
    bool interactWithDoor(bool opening);
};

#endif // TILE_H_INCLUDED
