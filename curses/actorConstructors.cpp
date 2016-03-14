#include "actor.h"

player::player(std::string speciesToLoad)
{
    coolDown=0;
    numberOfLegs=0;
    accuracy=100;
    defense=0;
    counter=0;
    onGround = false;
    sprinting=false;
    controlled=true;
    sprinting=false;
    int temp;
    z = 1;

    itemToPickUp = NULL;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    //attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    attack = 8000000;
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");
    skinColor = RSL::getStringData(fileName, speciesToLoad+".skinColor");
    rootPart = RSL::getBodyData(fileName, speciesToLoad+".limbs", temp, giveColor(skinColor));
    name = "player";

}

monster::monster(std::string speciesToLoad)
{
    nodeOn = NULL;
    coolDown=0;
    numberOfLegs=0;
    accuracy=100;
    defense=0;
    counter=0;
    onGround = false;
    sprinting=false;
    controlled=true;
    sprinting=false;
    int temp;
    z = 1;

    actorAttacking = NULL;
    itemToPickUp = NULL;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");
    skinColor = RSL::getStringData(fileName, speciesToLoad+".skinColor");
    rootPart = RSL::getBodyData(fileName, speciesToLoad+".limbs", temp, giveColor(skinColor));
    controlled=false;
    sprinting=false;
    goal = coordinate(-1,-1);
    memory=coordinate(-1,-1);
    post=coordinate(-1,-1);
    path.resize(0);
    name = "Monster";
}
