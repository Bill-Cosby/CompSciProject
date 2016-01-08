#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <vector>
#include <curses.h>

#define NUMBER_OF_COLORS 11

#define wood 9
#define stone 10
#define iron 11


class color_type
{
    public:
    int r,g,b;
    color_type(int _r, int _g, int _b){r=_r;g=_g;b=_b;}
};

void declareColors();


#endif // MATERIALS_H_INCLUDED
