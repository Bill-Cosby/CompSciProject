#ifndef BODYPARTS_H_INCLUDED
#define BODYPARTS_H_INCLUDED
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>


class item;

class bodyPart
{
public:

    bool left;
    std::vector<bodyPart*> attachedParts;
    std::string ID;
    std::string connectedTo;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture hairTex;
    sf::Sprite hair;
    std::string name;
    std::vector<std::string> equips;
    int weight;
    bool grasps;
    int damage;
    virtual bool equip(item* itemToGrasp, bool equipping){if (armor==NULL){armor = itemToGrasp;return true;}return false;}

    item * armor;
    item * vanity;

    bool wear(item* itemToWear){if (armor==NULL){armor= itemToWear;return true;}return false;}

    void draw(sf::RenderWindow &window, int x, int y, bool isPlayer);

    void clearDeadParts(bodyPart* partToCheck)
    {
        for (int i=0;i<attachedParts.size();i++){
            if (attachedParts[i]->damage <= 0){
                attachedParts.erase(attachedParts.begin()+i);
                std::cout << "Dead Parts Gone\n";
            }
            else{
                attachedParts[i]->clearDeadParts(partToCheck);
            }
        }
    }

    void setColors(sf::Color color, bool forHair, bool forEyes){
        if (forHair){
            if (name == "head")hair.setColor(color);
        }
        if (forEyes){
            if (name == "right eye" or name == "left eye"){
                sprite.setColor(color);
            }
        }
        if (!forHair and !forEyes){
            if (name != "right eye" and name != "left eye" and name != "hair")sprite.setColor(color);

        }
        for (bodyPart* _b : attachedParts){
            _b->setColors(color,forHair,forEyes);
        }
    }

    void heal(int value){
        damage+=value;
        if (damage > weight*2)damage = weight*2;
        for (bodyPart* _b : attachedParts){
            _b->heal(value);
        }
    }

    void setHair(sf::Texture tex)
    {
        if (name == "head"){
            hairTex = tex;
            hair.setTexture(hairTex);
        }
        else
        {
            for (bodyPart* _b : attachedParts){
                _b->setHair(tex);
            }
        }
    }

    bool findItem(item* itemToRemove, bool unequipping);

    void findEasiestHit(bodyPart *&bodyPartToHit, int &highestDamage, int probability, int attack, int myTotalWeight);
    bool canEquip(item* itemToGrasp, bool equipping);
    void returnParts(std::vector<bodyPart*> &returnBodyParts);
    void returnWeight(int &totalWeight);
};

struct eye : public bodyPart
{
public:
    bool left;
    eye(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    std::string color;

};

class hand : public bodyPart
{
public:
    item* inHand;
    bool equip(item* itemToGrasp, bool equipping);
    hand(std::string species,int _weight,  std::string id, std::string connectedto, bool Left, sf::Color color);
    hand(){inHand = NULL;armor=NULL;}
};

class foot : public bodyPart
{
public:
    item* sock;
    foot(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    foot(){sock = NULL;armor=NULL;}
};

class arm : public bodyPart
{
public:
    arm(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    bool hasHand(){return true;}
};

class leg : public bodyPart
{
public:
    leg(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    bool hasFoot(){return true;}
};

class torso : public bodyPart
{
public:
    bool severed_spine;
    torso(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color);
    torso(){armor=false;}

};

class tail : public bodyPart
{
public:
    tail(std::string species, int _weight, std::string id, std::string connectedto, sf::Color color);
};

class neck : public bodyPart
{
public:
    bool severed_spine;
    neck(std::string species,int _weight, std::string id, std::string connectedto, sf::Color color);
    neck(){armor = NULL;}
};

class head : public bodyPart
{
public:
    bool conscious;
    head(std::string species,int _weight, std::string id, std::string connectedto, sf::Color color);
    std::string color;
    head(){armor = NULL;}
};

std::string formatForParse(std::string species, std::string limb);



#endif // BODYPARTS_H_INCLUDED
