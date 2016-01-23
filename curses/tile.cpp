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

door::door(bool _o, short __material)
{
    open=_o;
//    openSymbol=RSL::getTextureData("data/textures/tiles.raw","opendoor.texture");
//    closedSymbol=RSL::getTextureData("data/textures/tiles.raw","door.texture");
    isDoor=true;
    _material=__material;
}

tile::tile(char dc, int mv, short mat)
{
    if (dc == '1'){
        texture = RSL::getTextureData("data/textures/tiles.raw","wall.texture");
    }
    else
    {
        texture = RSL::getTextureData("data/textures/tiles.raw","floor.texture");
    }
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,255,255,255));
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

