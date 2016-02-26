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

void tile::drawTile(sf::RenderWindow &window)
{
    sf::Sprite sprite;
    sprite.setPosition(position.x*16,position.y*16);
    if (defaultchar == '0')sprite.setTexture(floortex);
    if (defaultchar == '1')sprite.setTexture(wall);

    sprite.setColor(woodColor);

    window.draw(sprite);
}

door::door(bool _o, char dc, int mv, short mat) : tile(dc, mv, mat)
{
    open=_o;
    isDoor=true;
}

void door::drawTile(sf::RenderWindow &window)
{
    sf::Sprite sprite;
    if (isOpen()){
        sprite.setTexture(openDoor);
    }
    else{
        sprite.setTexture(closedDoor);
    }
    sprite.setColor(woodColor);
    sprite.setPosition(position.x*16,position.y*16);
    window.draw(sprite);
}

tile::tile(char dc, int mv, short mat)
{
    movementCost = mv;
    defaultchar = dc;
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

