#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>
#include "actor.h"
#include <SFML/Graphics.hpp>



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
int right;
int left;
int bottom;
int top;
std::vector<coordinate *> blank;

box(){blank.resize(2);}
void divideBox(int, std::vector<std::vector<tile*> > &);
void makeRoad(road*, std::vector<std::vector<tile*> > &);
};

class city: box
{
    public:
std::vector<std::vector<tile*> > tileMap;
void setTileMap(std::vector<std::vector<tile*> > & tileMap);
city(){left=0; bottom=0; right=24; top=24;}
void generateCity(std::vector<actor *> &,std::vector<item*> &, sf::RenderWindow&, announcements&);
void deleteTileMap(std::vector<std::vector<tile*> > & );
};



#endif // GENERATECITY_H_INCLUDED
