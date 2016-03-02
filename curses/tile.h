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

    int defaultchar;

    int movementCost;
    double elevation;
    std::string _material;
    tile(char dc,int mc, std::string mat);
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;};

    std::string giveMaterial(){return _material;}
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
    door(bool _o, int dc, int mv, std::string mat);
    void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
    bool interactWithDoor(bool opening);
    bool isOpen(){return open;}
};

#endif // TILE_H_INCLUDED
