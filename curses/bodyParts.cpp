
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
    bool didEquip = false;
    if (equipping == true){
        for (std::string _s : equips){
            if (_s == itemToGrasp->type){
                if (itemToGrasp->canEquip){
                    didEquip = equip(itemToGrasp,true);
                }
                else if (itemToGrasp->canWear){
                    std::cout << name << std::endl;
                    didEquip = equip(itemToGrasp,true);
                    if (didEquip) return true;
                }
            }
        }
    }
    for (bodyPart* _b : attachedParts){
        didEquip = _b->canEquip(itemToGrasp, equipping);
        if (didEquip) return true;
    }
    return didEquip;
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

void bodyPart::draw(sf::RenderWindow &window, int x, int y){
    std::cout << name << std::endl;
    if (vanity != NULL){
        if (left){
            vanity->sprite.scale(-1.0f,1.0f);
        }
        vanity->sprite.setPosition(x,y);
        window.draw(vanity->sprite);
    }
    else if (armor != NULL){
        armor->sprite.setPosition(x,y);
        if (left){
            armor->sprite.move(17,0);
            armor->sprite.setScale(-1.0f,1.0f);
        }
        window.draw(armor->sprite);
    }
    else{
        sprite.setPosition(x,y);
        window.draw(sprite);
    }

    for (bodyPart * _b : attachedParts){
        _b->draw(window,x,y);
    }
}

torso::torso(std::string species, int _weight,std::string id, std::string connectedto, sf::Color color)
{
    left = false;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    name="torso";
    grasps=false;
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "TORSO")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    equips.push_back("torso");
}

neck::neck(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color)
{
    left = false;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="neck";
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    //texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "NECK")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
}

head::head(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color)
{
    left = false;
    std::cout << species << std::endl;
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    name="head";
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    std::cout << formatForParse(species, "HEAD]") << std::endl;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "HEAD")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    equips.push_back("helm");
}

eye::eye(std::string species, int _weight, std::string id, std::string connectedto, bool _left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species,"EYE")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    left = _left;
    if (left==true){
        name = "left eye";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right eye";
    }
    armor = NULL;
    vanity = NULL;
    damage = weight*2;

}

hand::hand(std::string species, int _weight,  std::string id, std::string connectedto, bool _left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=true;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "HAND")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    left = _left;
    if (left==true){
        name = "left hand";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right hand";
    }
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    equips.push_back("glove");
    equips.push_back("onehand");
    equips.push_back("twohand");
}

arm::arm(std::string species, int _weight, std::string id, std::string connectedto, bool _left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "ARM")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    left = _left;
    if (left==true){
        name = "left arm";

        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.setScale(-1.0f,1.0f);
    }
    else{
        name = "right arm";
    }
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    equips.push_back("arm");
}

foot::foot(std::string species, int _weight, std::string id, std::string connectedto, bool _left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "FOOT")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    left = _left;
    if (left==true){
        name = "left foot";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right foot";
    }
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    equips.push_back("boot");
}

leg::leg(std::string species, int _weight,  std::string id, std::string connectedto, bool _left, sf::Color color)
{
    ID = id;
    connectedTo = connectedto;
    weight=_weight;
    grasps=false;
    texture = RSL::getTextureData("data/textures/creature_standard.raw", formatForParse(species, "LEG")+".texture");
    sprite.setTexture(texture);
    sprite.setColor(color);
    left = _left;
    if (left==true){
        name = "left leg";
        sprite.setOrigin(sprite.getPosition().x+17,0);
        sprite.scale(-1.0f,1.0f);
    }
    else{
        name = "right leg";
    }
    armor = NULL;
    vanity = NULL;
    damage = weight*2;
    equips.push_back("legging");
}

std::string formatForParse(std::string species, std::string limb)
{
    species.erase(species.begin()+species.size()-1);
    species.erase(species.begin()+0);
    return species+limb;
}
