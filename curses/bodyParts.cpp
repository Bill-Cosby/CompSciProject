
#include "bodyParts.h"
#include "RSL.h"
#include "item.h"

bool hand::equip(item* itemToGrasp, bool equipping)
{
    if (inHand==NULL){
        inHand = itemToGrasp;
        return true;
    }
    else {
        if (inHand == itemToGrasp){
            inHand=NULL;
        }
        else{
            inHand == itemToGrasp;
            return true;
        }
    }
    return false;
}

bool bodyPart::canEquip(item* itemToGrasp, bool equipping)
{
    if (equipping == true){
        for (std::string _s : equips){
            if (_s == itemToGrasp->type){
                if (itemToGrasp->canEquip){
                    equip(itemToGrasp,true);
                }
                else if (itemToGrasp->canWear){
                    std::cout << name << std::endl;
                    equip(itemToGrasp,true);
                }
            }
        }
    }
    for (bodyPart* _b : attachedParts){
        if (_b->canEquip(itemToGrasp,equipping)){
            return true;
        }
    }
    return false;
}

void bodyPart::findEasiestHit(bodyPart *&bodyPartToHit, int &highestDamage, int probability, int attack, int myTotalWeight)
{
    double temp;
    temp = rand()%myTotalWeight;

    if (temp < probability){
        probability = temp;
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

    for (bodyPart * _b : attachedParts){
        _b->findEasiestHit(bodyPartToHit,highestDamage,probability,attack,myTotalWeight);
    }
}

void bodyPart::returnParts(std::vector<bodyPart*> &returnBodyParts)
{
    returnBodyParts.push_back(this);

    for (bodyPart* _b : attachedParts){
        _b->returnParts(returnBodyParts);
    }
}

void bodyPart::returnWeight(int &totalWeight)
{
    totalWeight+=weight;
    for (bodyPart* _b : attachedParts){
        _b->returnWeight(totalWeight);
    }
}

torso::torso(std::string species, int _weight,std::string id, std::string connectedto, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    name="torso";
    grasps=false;
    armor = NULL;
    damage = weight*2;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "TORSO")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    equips.push_back("torso");
}

neck::neck(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="neck";
    armor = NULL;
    damage = weight*2;
    //texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "NECK")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
}

head::head(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color)
{
    std::cout << species << std::endl;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="head";
    armor = NULL;
    damage = weight*2;
    std::cout << formatForParse(species, "HEAD]") << std::endl;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "HEAD")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    equips.push_back("helm");
}

eye::eye(std::string species, int _weight, std::string id, std::string connectedto, bool left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species,"EYE")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
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

hand::hand(std::string species, int _weight,  std::string id, std::string connectedto, bool left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=true;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "HAND")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
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
    equips.push_back("glove");
    equips.push_back("onehand");
    equips.push_back("twohand");
}

arm::arm(std::string species, int _weight, std::string id, std::string connectedto, bool left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "ARM")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
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
    equips.push_back("arm");
}

foot::foot(std::string species, int _weight, std::string id, std::string connectedto, bool left, sf::Color color)
{
    std::cout << left << std::endl;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "FOOT")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
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
    equips.push_back("shoe");
}

leg::leg(std::string species, int _weight,  std::string id, std::string connectedto, bool left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "LEG")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
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
    equips.push_back("legging");
}

std::string formatForParse(std::string species, std::string limb)
{
    species.erase(species.begin()+species.size()-1);
    species.erase(species.begin()+0);
    return species+limb;
}
