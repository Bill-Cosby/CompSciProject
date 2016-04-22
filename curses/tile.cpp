#include "tile.h"

tile::tile(int hC, int cSF)
{
    hCost=hC;
    gCost=cSF;
    isContainer = false;
    isDoor=false;
}

tile::tile(coordinate pos, coordinate goal, int cSF)
{
    position=pos;
    hCost=getDistance(position,goal);
    gCost=cSF;
    isContainer = false;
    isDoor=false;
}

furniture::furniture(int dc, int movementCost, std::string material) : tile(dc,movementCost,material){}

void tile::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState)
{
    if (defaultchar == -1)return;
    sf::Sprite tempSprite;
    tempSprite.setTexture(textures[defaultchar]);
    tempSprite.setPosition(position.x*16,position.y*16);
    sf::Color tempColor = giveColor(_material);
    sf::Color darkenedColor;

    if (darkenBy <=.1){
        darkenedColor = sf::Color(30,30,30);
    }
    else{
         darkenedColor = sf::Color(tempColor.r*darkenBy,tempColor.g*darkenBy,tempColor.b*darkenBy);
    }

    tempSprite.setColor(darkenedColor);

    window.draw(tempSprite,renderState);
    darkenBy = 1;
}

door::door(bool _o, int dc, int mv, std::string mat) : tile(dc, mv, mat)
{
    _material = mat;
    open=_o;
    isDoor=true;
    darkenBy = 1;
    isContainer = false;
}

void door::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState)
{
    sf::Sprite tempSprite;
    sf::Color tempColor = giveColor(_material);
    sf::Color darkenedColor;
    if (darkenBy <.3){
        darkenedColor = sf::Color(30,30,30);
    }
    else{
         darkenedColor = sf::Color(tempColor.r*darkenBy,tempColor.g*darkenBy,tempColor.b*darkenBy);
    }

    tempSprite.setPosition(position.x*16,position.y*16);
        tempSprite.setColor(darkenedColor);

    if (isOpen()){
        tempSprite.setTexture(textures[woodfloor]);
        window.draw(tempSprite);
        tempSprite.setTexture(textures[opendoor]);
    }
    else{
        tempSprite.setTexture(textures[closeddoor]);
    }
    window.draw(tempSprite);
    darkenBy = 1;
}

tile::tile(char dc, int mv, std::string mat)
{
    _material = mat;
    movementCost = mv;
    defaultchar = dc;
    darkenBy = 1;
    isContainer = false;
}

container::container(int dc, int mov, std::string mat) : tile(dc,mov,mat){isContainer = true;fillWithArmor();}

void container::fillWithArmor()
{
    int dumbNumber = rand()%11;
    int randomNumber = RSL::getIntData("data/items/armor_type.raw","numberofitems.number",0);

    for (int i =0; i<dumbNumber;i++){
        std::string name = RSL::returnRandomItem("data/items/armor_type.raw",rand()%randomNumber+1);
        int value = RSL::getIntData("data/items/armor_type.raw",name+".value",0);

    }
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

