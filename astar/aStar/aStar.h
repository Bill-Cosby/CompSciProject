#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "include/curses.h"

template<class T>
class BST
{
public:

    T value;

    BST* Left;
    BST* Right;

//  constructor
    BST(T item);
//  methods
    void add(BST* item);
    T give();
};

template <class T>
class baseNode
{
public:
    BST<T>* child;

    T give();
    void add(BST<T>* item);
};

class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();

    bool operator == (coordinate _c){return (x==_c.x and y==_c.y);}
};

class node
{
public:
    //important coordinates
    coordinate position;
    coordinate parent;

    //integer declarations
    int gCost;
    int hCost;

    //automatic variables
    int fCost(){
        return gCost+hCost;
    }

    //constructors
    node(coordinate,coordinate, int);
    node();

    bool operator == (node _n){return (position==_n.position/*,parent==_n.parent,gCost==_n.gCost,hCost==_n.hCost*/);}
};

std::vector<coordinate> pathFinder(bool[][20], coordinate, coordinate);
std::vector<node> getNeighbors(node,bool[][20],coordinate,int);

float heuristic(coordinate,coordinate);
int getDistance(coordinate, coordinate);
bool nodeVectorContains(std::vector<node>, node);
bool nodeLibraryContains(std::vector<BST<node> >, node);

#endif // ASTAR_H_INCLUDED
