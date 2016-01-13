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
void tile::find_material()
{
   if(elevation<=-1.0000)
    {
        material=1;
        defaultchar='1';
    }
   else if(elevation<=-0.1500)
    {
        material=2;
        defaultchar='2';
    }
   else if(elevation<=0.0000)
    {
        material=3;
        defaultchar='3';
    }
   else if(elevation<=0.0625)
    {
        material=4;
        defaultchar='4';
    }
   else if(elevation<=0.1250)
    {
        material=5;
        defaultchar='5';
    }
   else if(elevation<=0.7500)
    {
        material=6;
        defaultchar='6';
    }
   else if(elevation<=1.200)
    {
        material=7;
        defaultchar='7';
    }
}
