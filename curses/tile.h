#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"
#include "RSL.h"
#include "materials.h"
#include <SFML/Graphics.hpp>

class tile : public node
{
public:

    int width, height;

    bool isDoor;
    bool isContainer;
    bool visible;

    float darkenBy;
    bool litHere;

    char defaultchar;

    int movementCost;
    double elevation;
    short _material;
    tile(char dc,int mc, short mat);
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;};

    short giveMaterial(){return _material;}
    void find_material();

    virtual void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
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
    door(bool _o, char dc, int mv, short mat);
    void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
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
