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

    std::vector<bodyPart*> attachedParts;
    std::string ID;
    std::string connectedTo;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
    std::vector<std::string> equips;
    int weight;
    bool grasps;
    int damage;
    virtual bool equip(item* itemToGrasp, bool equipping){armor = itemToGrasp;}

    item * armor;
    item * vanity;

    bool wear(item* itemToWear){if (armor==NULL){armor= itemToWear;return true;}return false;}

    void draw(sf::RenderWindow &window, int x, int y){
        sprite.setPosition(x,y);
        window.draw(sprite);

        for (bodyPart * _b : attachedParts){
            _b->draw(window,x,y);
        }
    }

    void clearDeadParts(bodyPart* partToCheck)
    {
        for (int i=0;i<attachedParts.size();i++){
            if (attachedParts[i]== partToCheck){
                attachedParts.erase(attachedParts.begin()+i);
            }
            else{
                attachedParts[i]->clearDeadParts(partToCheck);
            }
        }
    }


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
    bool left;
    item* inHand;
    bool equip(item* itemToGrasp, bool equipping);
    hand(std::string species,int _weight,  std::string id, std::string connectedto, bool Left, sf::Color color);
    hand(){inHand = NULL;armor=NULL;}
};

class foot : public bodyPart
{
public:
    bool left;
    item* sock;
    foot(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    foot(){sock = NULL;armor=NULL;}
};

class arm : public bodyPart
{
public:
    bool left;
    arm(std::string species,int _weight, std::string id, std::string connectedto, bool Left, sf::Color color);
    bool hasHand(){return true;}
};

class leg : public bodyPart
{
public:
    bool left;
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
