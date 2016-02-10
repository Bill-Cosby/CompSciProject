
#include "bodyParts.h"
#include "RSL.h"

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

torso::torso(std::string species, int _weight)
{
    weight=_weight;
    grasps=false;
    name="torso";
    armor = NULL;
    damage = 0;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humantorso.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
}

neck::neck(std::string species, int _weight)
{
    weight=_weight;
    grasps=false;
    name="neck";
    armor = NULL;
    damage = 0;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanhead.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
}

head::head(std::string species, int _weight)
{
    weight=_weight;
    grasps=false;
    name="head";
    armor = NULL;
    damage = 0;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humanhead.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,200,181));
}

eye::eye(std::string species, int _weight, bool _left)
{
    weight=_weight;
    left=_left;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", "humaneye.texture");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255,0,1));
    if (left==true){
        name = "left eye";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right eye";
    }
    armor = NULL;
    damage = 0;
}

hand::hand(std::string species, int _weight, bool _left)
{
    weight=_weight;
    left=_left;
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
    damage = 0;
}

arm::arm(std::string species, int _weight, bool _left)
{
    weight=_weight;
    left=_left;
    _hand=hand(species,1,left);
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
    damage = 0;
}

foot::foot(std::string species, int _weight, bool _left)
{
    weight=_weight;
    left=_left;
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
    damage = 0;
}

leg::leg(std::string species, int _weight, bool _left)
{
    weight=_weight;
    left=_left;
    _foot=foot(species,1,left);
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
    damage = 0;
}
