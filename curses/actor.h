#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <vector>
#include "tile.h"

class player
{
public:
    int x,y;
    char symbol;
    void movement(std::vector<std::vector<tile> >,char);
    player();
};

#endif // ACTOR_H_INCLUDED
