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

    if (occupied!=NULL){
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

    if (open){
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

container::container(int dc, int mov, std::string mat,int x, int y) : tile(dc,mov,mat,x,y){isContainer = true;fillWithArmor();}

void container::fillWithArmor()
{
    int dumbNumber = rand()%11;
    int randomNumber;
    int matNumber;

    for (int i =0; i<dumbNumber;i++){
        matNumber = rand()%10 + 1;
        randomNumber = rand()%RSL::getIntData("data/items/armor_type.raw","numberofitems.number",0)+1;
        std::string name =  RSL::returnRandomItem("data/items/armor_type.raw",randomNumber);
        int value = RSL::getIntData("data/items/armor_type.raw",name+".value",0);

        if(randomNumber>6)
        {
            contained.push_back(new clothing(name,'C',0,0,5,"cotton"));
        }
        else if(matNumber == 1 or matNumber == 2 or matNumber == 3 or matNumber == 4)
        {
            contained.push_back(new clothing(name,'C',0,0,5,"cotton"));
        }
        else if(matNumber == 5 or matNumber == 6 or matNumber == 7)
        {
            contained.push_back(new clothing(name,'C',0,0,5,"copper"));
        }
        else if(matNumber == 8 or matNumber == 9)
        {
            contained.push_back(new clothing(name,'C',0,0,5,"iron"));
        }
        else if(matNumber == 10)
        {
            contained.push_back(new clothing(name,'C',0,0,5,"steel"));
        }

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

