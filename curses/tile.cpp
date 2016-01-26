#include "tile.h"

tile::tile(int hC, int cSF)
{
    hCost=hC;
    gCost=cSF;
    isDoor=false;
}

tile::tile(coordinate pos, coordinate goal, int cSF)
{
    position=pos;
    hCost=getDistance(position,goal);
    gCost=cSF;
    isDoor=false;
}

door::door(bool _o, short _material)
{
    open=_o;
    openSymbol=']';
    closedSymbol='Æ';
    isDoor=true;
    material=_material;
}

bool door::interactWithDoor(bool opening)
{
    if (open==false){
        if (opening==true){
            open=true;
            return false;
        }
        return false;
    }
    else{
        if (opening==false){
            open=false;
            return true;
        }
        return true;
    }
}

void tile::findColor()
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
