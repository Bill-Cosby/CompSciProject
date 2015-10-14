#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class tile
{
public:
    bool corner;
    char occupychar;
    char defaultchar;
    int movementCost;
    tile(char oc,char dc,int mc){occupychar=oc;defaultchar=dc;movementCost=mc;};
    tile(){corner=false;};
};

#endif // TILE_H_INCLUDED
