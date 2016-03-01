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

void tile::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState)
{
    if (darkenBy == 0)return;

    sf::Sprite sprite;
    sprite.setPosition(position.x*16,position.y*16);
    sf::Color tempColor = giveColor(_material);
    sprite.setTexture(giveTexture(defaultchar));

    sprite.setColor(tempColor);

    window.draw(sprite,renderState);
    darkenBy = 0;
}

door::door(bool _o, char dc, int mv, std::string mat) : tile(dc, mv, mat)
{
    open=_o;
    isDoor=true;
    darkenBy = 0;
}

void door::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState)
{
    if (darkenBy == 0)return;
    sf::Sprite sprite;
    sf::Color tempColor = giveColor(_material);
    sprite.setColor(tempColor);
    sprite.setPosition(position.x*16,position.y*16);
    if (isOpen()){
        sprite.setTexture(woodfloor);
        window.draw(sprite);
        sprite.setTexture(openDoor);
    }
    else{
    sprite.setTexture(giveTexture(defaultchar));
    }
    window.draw(sprite, renderState);
    darkenBy = 0;
}

tile::tile(char dc, int mv, std::string mat)
{
    movementCost = mv;
    defaultchar = dc;
    darkenBy = 0;
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

