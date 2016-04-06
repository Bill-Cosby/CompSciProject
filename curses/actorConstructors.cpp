#include "actor.h"

player::player(std::string speciesToLoad)
{
    actorFollowing = NULL;
    coolDown=0;
    numberOfLegs=0;
    accuracy=100;
    defense=0;
    counter=0;

    onGround = false;
    sprinting= false;
    controlled=true;
    sprinting= false;
    inDanger = false;
  equipsArmor= false;
    opensdoors=false;
    int temp;
    z = 1;

    itemToPickUp = NULL;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    //attack = RSL::getIntData(fileName, speciesToLoad+".strength",0);
    attack = 700000;
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity",0);
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");
    skinColor = RSL::getStringData(fileName, speciesToLoad+".skinColor");
    rootPart = RSL::getBodyData(fileName, speciesToLoad+".limbs", temp, giveColor(skinColor), giveColor(eyeColor));
    name = giveName();
    equipment.push_back(new clothing("cottonshirt",'C',0,0,10,"cotton"));
    equipment.push_back(new clothing("cottonpants",'C',0,0,5,"cotton"));
    equipment.push_back(new clothing("cottonpants",'C',0,0,5,"cotton"));
    rootPart->equip(equipment[0],true);
    rootPart->equip(equipment[1],true);
    rootPart->equip(equipment[2],true);

    if (RSL::getStringData(fileName, speciesToLoad+".EVIL") == "true")EVIL = true;
    else EVIL = false;
    if (RSL::getStringData(fileName,speciesToLoad+".SOCIAL") == "true")social = true;
    else social = false;
    if (RSL::getStringData(fileName,speciesToLoad+".EQUIPS") == "true")social = true;
    else social = false;
    if (RSL::getStringData(fileName,speciesToLoad+".OPENDOORS") == "true")social = true;
    else social = false;

}

monster::monster(std::string speciesToLoad)
{
    actorFollowing = NULL;
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
    inDanger = false;
    int temp;
    z = 1;

    actorAttacking = NULL;
    itemToPickUp = NULL;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength",0);
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity",0);
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");
    skinColor = RSL::getStringData(fileName, speciesToLoad+".skinColor");
    rootPart = RSL::getBodyData(fileName, speciesToLoad+".limbs", temp, giveColor(skinColor), giveColor(eyeColor));
    name = giveName();
    equipment.push_back(new clothing("cottonshirt",'C',0,0,10,"cotton"));
    equipment.push_back(new clothing("cottonpants",'C',0,0,5,"cotton"));
    equipment.push_back(new clothing("cottonpants",'C',0,0,5,"cotton"));
    rootPart->equip(equipment[0],true);
    rootPart->equip(equipment[1],true);
    rootPart->equip(equipment[2],true);

    controlled=false;
    sprinting=false;

    if (RSL::getStringData(fileName, speciesToLoad+".EVIL") == "true")EVIL = true;
    else EVIL = false;
    if (RSL::getStringData(fileName,speciesToLoad+".SOCIAL") == "true")social = true;
    else social = false;
    if (RSL::getStringData(fileName,speciesToLoad+".EQUIPS") == "true")social = true;
    else social = false;
    if (RSL::getStringData(fileName,speciesToLoad+".OPENDOORS") == "true")social = true;
    else social = false;

    goal = coordinate(-1,-1);
    memory=coordinate(-1,-1);
    interactedWithDoor = false;
}
