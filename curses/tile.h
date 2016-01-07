#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"
#include "materials.h"

class tile : public node
{
public:
    bool isDoor;
    char defaultchar;
    int movementCost;
    short material;
    tile(char dc,int mc, short mat){defaultchar=dc;movementCost=mc;material=mat;}
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;};

    short giveMaterial(){return material;}

    virtual char drawTile(){return defaultchar;}
    virtual bool interactWithDoor(bool opening){}
    virtual bool isOpen(){}
};

class door : public tile
{
public:
    bool open;
    char openSymbol;
    char closedSymbol;
    door(bool _o, short);
    char drawTile(){if (open==true){return openSymbol;}return closedSymbol;}
    bool interactWithDoor(bool opening);
    bool isOpen(){return open;}
};

class container : public tile

#endif // TILE_H_INCLUDED
