#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED


class tile
{
public:
    char occupychar;
    char defaultchar;
    int movementCost;
    int x;
    int y;
    int color;
    tile(char oc,char dc,int mc){occupychar=oc;defaultchar=dc;movementCost=mc;};
    tile(){};
    void find_color();
    double elevation;

};


#endif // TILE_H_INCLUDED

