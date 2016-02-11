#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>
#include "actor.h"

class road
{
    public:
coordinate * Point1;
coordinate * Point2;
int Size;
bool vertical;

};


class box
{
public:

box * subBox1;
box * subBox2;
double right;
double left;
double bottom;
double top;
std::vector<coordinate *> blank;

box(){blank.resize(2);}
void divideBox(int,std::vector<std::vector<tile*> >&);
void makeRoad(road*,std::vector<std::vector<tile*> > &);
};

class city: public box
{
std::vector <road *> roads;
city(){left=0; bottom=0; right=50; top=50;}
void setTileMap(std::vector<std::vector<tile*> >&);
void deleteTileMap(std::vector<std::vector<tile*> >&);
void generateCity(std::vector<actor *> &,std::vector<item*> &, sf::RenderWindow&, announcements&);
void makeCity();

};




#endif // GENERATECITY_H_INCLUDED
