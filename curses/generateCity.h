#ifndef GENERATECITY_H_INCLUDED
#define GENERATECITY_H_INCLUDED
#include "tile.h"
#include <time.h>
#include <random>
#include <vector>
#include "actor.h"
#include <SFML/Graphics.hpp>
#include <chrono>




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

box(){left = 0;right =0;top=0;bottom=0;}
~box();
void divideBox(int, std::vector<std::vector<std::vector<tile*> > > &, std::string, std::mt19937 &);
void makeLine(road*, std::vector<std::vector<std::vector<tile*> > > &, int, std::string, std::mt19937 &);
void makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::mt19937 &);
};


class city: public box
{
    public:
 std::mt19937 generator;
unsigned seed;
int width;
int height;
std::vector<std::vector<std::vector<tile*> > > tileMap;
void setTileMap();
city(){width=100; height=100; left=0; bottom=0; right=width-1; top=height-1; seed=std::chrono::system_clock::now().time_since_epoch().count(); generator.seed(seed);}
void generateCity();
~city();

};



#endif // GENERATECITY_H_INCLUDED
