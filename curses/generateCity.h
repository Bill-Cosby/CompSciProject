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
void divideBox(int, std::vector<std::vector<std::vector<tile*> > > &, std::string, std::mt19937 &);
void makeLine(road*, std::vector<std::vector<std::vector<tile*> > > &, int, std::string, std::mt19937 &);
void makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::mt19937 &);
};


class city: public box
{
    bool oneSmallStepForMan;
    public:
 std::mt19937 generator;
unsigned seed;
int width;
int height;
city(int xZero, int yZero, int w, int h, std::vector<std::vector<std::vector<tile*> > > & tileMap);
void setTileMap(std::vector<std::vector<std::vector<tile*> > > & tileMap);

//~city();

};



#endif // GENERATECITY_H_INCLUDED
