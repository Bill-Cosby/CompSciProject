#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"
#include "materials.h"

class tile : public node
{
public:
    bool isDoor;
    bool isContainer;
    char defaultchar;
    int movementCost;
    double elevation;
    short material;
    tile(char dc,int mc, short mat){defaultchar=dc;movementCost=mc;material=mat;}
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;};

    short giveMaterial(){return material;}
    void find_material();

    virtual char drawTile(){return defaultchar;}
    virtual bool interactWithDoor(bool opening){}
    virtual bool isOpen(){}
    virtual void openContainer(){}
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
{
    std::string name;
public:
    std::vector<item*> contains;
    void openContainer();
};

#endif // TILE_H_INCLUDED
