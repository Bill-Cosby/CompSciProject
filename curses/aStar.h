#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <iostream>
#include <curses.h>
#include "tile.h"
#include <queue>
#include <sstream>


std::vector<node> findNeighbors(std::vector<std::vector<tile> >, node, coordinate);
std::vector<coordinate> pathFinder(std::vector<std::vector<tile*> > ,coordinate,coordinate, std::vector<coordinate>);
bool canSee(std::vector<std::vector<tile*> > test_map, coordinate checkSpot, coordinate spotToCheck);
bool vectorContains(std::vector<tile>,tile);

#endif // ASTAR_H_INCLUDED
