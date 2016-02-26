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
    sprite.setColor(woodColor);
}

void tile::drawTile(sf::RenderWindow &window)
{
    sf::Sprite sprite;
    sprite.setPosition(x*16,y*16);
    if (defaultchar == '0')sprite.setTexture(floor);
    if (defaultchar == '1')sprite.setTexture(door);

    sprite.setColor(woodColor);

    window.draw(sprite);
}

door::door(bool _o, char dc, char mv, short mat) : tile(dc, mv, mat)
{
    open=_o;
    isDoor=true;
    sprite.setColor(woodColor);
}

void door::drawTile(sf::RenderWindow &window)
{
    if (isOpen()){
        sprite.setTexture(texture);
        window.draw(sprite);
        sprite.setTexture(openSymbol);
    }
    else{
        sprite.setTexture(closedSymbol);
    }
    window.draw(sprite);
}

tile::tile(char dc, int mv, short mat)
{
    movementCost = mv;
    sprite.setTexture(texture);
    sprite.setColor(woodColor);
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

