
#include "bodyParts.h"
#include "RSL.h"
#include "item.h"

void hand::equip(item* itemToGrasp, bool equipping)
{
    if (inHand==NULL){
        inHand = itemToGrasp;
    }
    else {
        if (inHand == itemToGrasp){
            inHand=NULL;
        }
        else{
            inHand == itemToGrasp;
        }
    }
}

void bodyPart::findEasiestHit(bodyPart * bodyPartToHit, int &highestDamage, int probability, int attack, int myTotalWeight)
{
    srand(time(NULL));
    srand(rand()%time(NULL));
    double temp;

    if (rand()%probability < myTotalWeight){
        if (armor!=NULL){
            if((armor->defense + weight) - attack < highestDamage){
                bodyPartToHit = this;
                temp = rand()%attack+1;
                highestDamage = armor->defense + weight - temp;
            }
        }
        else{
            if (weight - attack < highestDamage){
                bodyPartToHit = this;
                temp = rand()%attack+1;
                highestDamage = weight - temp;
            }
        }
    }
    findEasiestHit(bodyPartToHit,highestDamage,probability,attack,myTotalWeight);
}

torso::torso(std::string species, int _weight,std::string id, std::string connectedto)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    name="torso";
    grasps=false;
    armor = NULL;
    damage = weight*2;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humantorso.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));

}

neck::neck(std::string species, int _weight, std::string id, std::string connectedto)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="neck";
    armor = NULL;
    damage = weight*2;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanhead.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));

}

head::head(std::string species, int _weight, std::string id, std::string connectedto)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="head";
    armor = NULL;
    damage = weight*2;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanhead.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));

}

eye::eye(std::string species, int _weight, std::string id, std::string connectedto, bool left)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humaneye.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0,0,255));
    if (left==true){
        name = "left eye";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right eye";
    }
    armor = NULL;
    damage = weight*2;

}

hand::hand(std::string species, int _weight,  std::string id, std::string connectedto, bool left)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=true;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanhand.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
    if (left==true){
        name = "left hand";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right hand";
    }
    armor = NULL;
    damage = weight*2;

}

arm::arm(std::string species, int _weight, std::string id, std::string connectedto, bool left)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanarm.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
    if (left==true){
        name = "left arm";

        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.setScale(-1.0f,1.0f);
    }
    else{
        name = "right arm";
    }
    armor = NULL;
    damage = weight*2;

}

foot::foot(std::string species, int _weight, std::string id, std::string connectedto, bool left)
{
    std::cout << left << std::endl;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanfoot.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
    if (left==true){
        name = "left foot";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right foot";
    }
    armor = NULL;
    damage = weight*2;

}

leg::leg(std::string species, int _weight,  std::string id, std::string connectedto, bool left)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanleg.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
    if (left==true){
        name = "left leg";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right leg";
    }
    armor = NULL;
    damage = weight*2;

}
