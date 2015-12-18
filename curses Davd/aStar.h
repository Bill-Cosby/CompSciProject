#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <iostream>
#include "include/curses.h"
#include "tile.h"
#include "node.h"
#include <queue>


std::vector<node> findNeighbors(std::vector<std::vector<tile> >, node, coordinate);
std::vector<coordinate> pathFinder(std::vector<std::vector<tile> > ,coordinate,coordinate, std::vector<coordinate>);
bool vectorContains(std::vector<tile>,tile);

#endif // ASTAR_H_INCLUDED
