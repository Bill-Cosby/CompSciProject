#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <vector>
#include "tile.h"

class actor
{
    int x,y;
    char _symbol;
public:
    void movement(std::vector<std::vector<tile> >,char);
    actor();
    int row(){return y;}
    int col(){return x;}
    char symbol(){return _symbol;}
    void pos(int _y,int _x){x=_x;y=_y;}
};

#endif // ACTOR_H_INCLUDED
