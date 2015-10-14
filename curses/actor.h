#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <vector>
#include "tile.h"

class actor
{
    int _row,_col;
    char _symbol;
public:
    actor(char c,int r,int coll){_symbol=c;_row=r;_col=coll;}
    void pos(int row, int col);
    int row(){return _row;}
    int col(){return _col;}
    char symbol(){return _symbol;}
    void movement(std::vector<std::vector<tile> > map_, char ch);
};

#endif // ACTOR_H_INCLUDED
