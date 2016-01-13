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
    if(elevation<=-1)
    {
        material=1;
        defaultchar='~';
    }
    else if(elevation<=-.25){
        material = 1;
        defaultchar='~';
    }
    else if(elevation<=0){
        material = wood;
        defaultchar = '`';
    }
    else if(elevation<=.0625){
        material = wood;
        defaultchar = ',';
    }
    else if (elevation<=.125){
        material = grass;
        defaultchar = '"';
    }
    else if (elevation <= .3750){
        material = iron;
        defaultchar = '.';
    }
    else if (elevation <= .75){
        material = stone;
        defaultchar = '*';
    }
    else
    {
        material = COLOR_WHITE;
        defaultchar = '-';
    }
}
