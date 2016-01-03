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

door::door(bool _o)
{
    open=_o;
    openSymbol=']';
    closedSymbol=220;
    isDoor=true;
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
