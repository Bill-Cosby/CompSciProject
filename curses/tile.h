#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
#include "item.h"
#include "node.h"
#include "RSL.h"
#include "materials.h"
#include <SFML/Graphics.hpp>

class actor;

class tile : public node
{
public:

    actor* occupied;

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
    tile(char dc,int mc, std::string mat, int x, int y);
    tile(coordinate,coordinate,int);
    tile(int hCost, int costSoFar);
    tile(coordinate pos);
    tile(){defaultchar = -1;isDoor=false;movementCost = 0;_material = "NULL";};

    std::string giveMaterial(){return _material;}
    void find_material();
    void findPerlin(coordinate position);

    virtual void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState);
    virtual bool interactWithDoor(bool opening){return false;}
    virtual bool isOpen(){return true;}
    virtual std::vector<item*> openContainer(){}
    virtual bool isSocial(){return false;}
    virtual void fillWithArmor(){}
    virtual void setItems(std::vector<item*> items){}
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
    door(bool _o, int dc, int mv, std::string mat,int x, int y);
    void drawTile(sf::RenderWindow &window, sf::RenderStates &renderState, int x,int y);
    bool interactWithDoor(bool opening);
    bool isOpen(){return open;}
};

class furniture : public tile
{
public:
    furniture(int dc, int movementCost, std::string material,int x, int y);
};

class container : public tile
{
public:
    std::vector<item*> contained;
    std::vector<item*> openContainer(){return contained;}
    container(int dc, int movementCost, std::string material,int x, int y);
    void fillWithArmor();
    void setItems(std::vector<item*> items){contained = items;}
};

#endif // TILE_H_INCLUDED
