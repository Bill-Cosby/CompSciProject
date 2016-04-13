#include "tile.h"
#include "actor.h"

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

furniture::furniture(int dc, int movementCost, std::string material,int x, int y) : tile(dc,movementCost,material,x,y){}

void tile::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState)
{
    if (defaultchar != -1){
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
    }

    else if (occupied!=NULL){
        std::cout << "We here\n";
        occupied->drawActor(window,position.x,position.y);
    }

    darkenBy = 1;
}

door::door(bool _o, int dc, int mv, std::string mat,int x, int y) : tile(dc, mv, mat,x,y)
{
    _material = mat;
    open=_o;
    isDoor=true;
    darkenBy = 1;
    isContainer = false;
}

void door::drawTile(sf::RenderWindow &window, sf::RenderStates &renderState,int x,int y)
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

tile::tile(coordinate pos){position = pos;}

tile::tile(char dc, int mv, std::string mat, int x, int y) : tile(coordinate(x,y))
{
    _material = mat;
    movementCost = mv;
    defaultchar = dc;
    darkenBy = 1;
    isContainer = false;
    occupied = NULL;
}

container::container(int dc, int mov, std::string mat) : tile(dc,mov,mat){isContainer = true;fillWithArmor();}

void container::fillWithArmor()
{
    int dumbNumber = rand()%11;
    int randomNumber = RSL::getIntData("data/items/armor_type.raw","numberofitems.number",0);


    for (int i =0; i<dumbNumber;i++){
        std::string name = RSL::returnRandomItem("data/items/armor_type.raw",rand()%randomNumber+1);
        int value = RSL::getIntData("data/items/armor_type.raw",name+".value",0);

        contained.push_back(new clothing(name,'p',0,0,value,"iron"));
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

