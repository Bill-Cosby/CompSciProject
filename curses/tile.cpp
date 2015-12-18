#include "tile.h"


void tile::find_color()
{
   if(elevation<-1.0000)
    {
        color=1;
    }
   else if(elevation<-0.2500)
    {
        color=2;
    }
   else if(elevation<0.0000)
    {
        color=3;
    }
   else if(elevation<0.0625)
    {
        color=4;
    }
   else if(elevation<0.1250)
    {
        color=5;
    }
   else if(elevation<0.7500)
    {
        color=6;
    }
   else if(elevation<1.200)
    {
        color=7;
    }
}


