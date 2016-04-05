#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"
#include "RSL.h"
#include "materials.h"
#include <SFML/Graphics.hpp>

/*
class grass:Tile
{
*/
class tile : public node
{
public:

    int width, height;

    bool isDoor;
    bool isContainer;
    bool visible;

    std::vector<double> color;
    float darkenBy;
    bool litHere;


    int defaultchar;

    int movementCost;
    double elevation;
    std::string _material;
    tile(char dc,int mc, std::string mat);
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(){isDoor=false;movementCost = 0;_material = "NULL";};

    std::string giveMaterial(){return _material;}
    void find_material();
    void SetColor();
    void findPerlin(coordinate position);

    virtual void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
    virtual bool interactWithDoor(bool opening){}
    virtual bool isOpen(){return true;}
    virtual void openContainer(){}
    virtual bool isSocial(){return false;}
};

class socialTile : public tile
{
public:
    bool emitsLight;
    virtual bool isSocial(){return true;}
    socialTile(int dc, int mv, std::string mat){defaultchar = dc;movementCost = mv; _material = mat;}
};

class door : public tile
{
public:
    bool open;
    int openSymbol;
    int closedSymbol;
    door(bool _o, int dc, int mv, std::string mat);
    void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
    bool interactWithDoor(bool opening);
    bool isOpen(){return open;}
};

class furniture : public tile
{
public:
    furniture(int dc, int movementCost, std::string material);
};

class container : public tile
{
    std::vector<item*> contained;
    void openContainer();
};

#endif // TILE_H_INCLUDED
