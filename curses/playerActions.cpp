#include "actor.h"

void player::movement(std::vector<std::vector<std::vector<tile*> > > &_map,std::vector<item*> &localItems, std::vector<actor*> &actors, sf::RenderWindow &window, bool &keyrelease, announcements & announcementList, const double waterBelow)
{
    /*
    0 = NORTH
    1 = CENTER
    2 = SOUTH
    3 = EAST
    4 = WEST
    5 = NORTH-WEST
    6 = NORTH-EAST
    7 = SOUTH-EAST
    8 = SOUTH-WEST
    9 = CLOSE DOOR
    10 = OPEN DOOR
    11 = INVENTORY
    12 = PAUSE(options, quit game)/EXIT MENU
    13 = STATS
    14 = EXAMINE
    15 = EXECUTE
    16 = LOOK
    */
    int ch;
    coordinate temp = coordinate(x,y);
    bool moveThroughDoor=true;
    bool attacking=false;
    bool pressedKey = false;
    char inventoryMovement;
    char closeDirection;
    char examineDirection;
    std::vector<item*> itemsExamining;

    sf::Event event;

    tile tempFuckdebugging;
    coordinate tempShit=coordinate(x,y);
    customSpeed=speed();
    if (counter>=customSpeed)
        {

                while (window.pollEvent(event)){
                    if (event.type == sf::Event::KeyPressed){
                        pressedKey = true;
                    }
                }
            pressedKey = false;

                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){temp.x++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){temp.y--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){temp.y++;keyrelease=false;}



            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){openInventory(window,localItems, keyrelease);}

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                while (pressedKey == false){
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::KeyPressed){
                                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){temp.y++;keyrelease=false;}
                            pressedKey = true;
                        }
                    }
                }
                _map[1][temp.y][temp.x]->interactWithDoor(false);
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                while (pressedKey == false){
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::KeyPressed){

                                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){temp.y++;keyrelease=false;}
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){keyrelease=false;}
                            pressedKey = true;

                        }
                    }
                }
                examineGround(window,localItems,temp, announcementList);
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

                    }
                    pressedKey = false;
                    while (keyrelease == true){
                             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){temp.x++;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){temp.x--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){temp.y--;keyrelease=false;}
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){temp.y++;keyrelease=false;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){keyrelease=false;}
                        pressedKey = true;
                    }
                    for (actor* _a : actors){
                        if (coordinate(_a->col(),_a->row()) == temp){
                            actorAttacking = _a;
                        }
                    }
                    attackEnemy(_map,announcementList,localItems,window);
                    actorAttacking = NULL;
                }
            }
            else if ((_map[1][temp.y][temp.x]->movementCost != -1 and _map[0][temp.y][temp.x]->movementCost != -1 and playerInBoat==false) or (playerInBoat==true and _map[0][temp.y][temp.x]->elevation<=waterBelow+0.05)){if(playerInBoat==true){std::cout<<"MMMM";}
                if (_map[1][temp.y][temp.x]->isDoor){
                    moveThroughDoor = _map[1][temp.y][temp.x]->interactWithDoor(true);
                }
                for (actor* _a : actors){
                    if (_a == this)continue;
                    if (coordinate(_a->col(),_a->row()) == temp){
                        actorAttacking = _a;
                        simpleAttackEnemy(_map,announcementList,localItems);
                        return;
                    }
                }
                if (moveThroughDoor == true){
                    pos(temp.y,temp.x);
                    counter=0;
                }
            }
            else{


            }


        sprite.setPosition(x*16,y*16);
    }
    counter++;
}

void player::attackEnemy(std::vector<std::vector<std::vector<tile*> > >& _map, announcements& announcementList, std::vector<item*> &localItems, sf::RenderWindow &window)
{
    window.setView(window.getDefaultView());
    if (actorAttacking==NULL)return;
    float temp;
    int buttonSelected = 0;

    std::vector<int> attackValues;
    std::vector<float> probabilityValues;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);

    std::vector<bodyPart*>bodyPartList;
    actorAttacking->rootPart->returnParts(bodyPartList);


    for (bodyPart* _b : bodyPartList){
        if (_b->armor !=NULL)temp = (_b->damage) - totalAttack()/_b->armor->defense;
        else temp = (_b->damage - totalAttack());
        if (temp < 0){
            temp = 0;
        }
        attackValues.push_back(temp);
        temp = rand()%_b->weight;
        float playerAbility = rand()%dexterity;
        probabilityValues.push_back((int)(((temp/actorAttacking->totalWeight())+playerAbility/dexterity)*100));
    }
    std::stringstream stream;
    sf::Event event;
    while (true){
        window.clear();
        text.setString("Body part");
        text.setPosition(25,0);
        window.draw(text);
        for(int i = 0;i<bodyPartList.size();i++){
            if (i ==  buttonSelected)text.setStyle(sf::Text::Underlined);
            text.setString(bodyPartList[i]->name);
            text.setPosition(25,35+i*16);
            window.draw(text);
            text.setStyle(sf::Text::Regular);
        }
        text.setString("   health\n Post Attack");
        text.setPosition(200,0);
        window.draw(text);
        for (int i=0;i<attackValues.size();i++){
            stream << attackValues[i];
            text.setString(stream.str());
            stream.str(std::string());
            stream.clear();
            text.setPosition(250,35+i*16);
            window.draw(text);
        }
        text.setString("Chance (higher is better)");
        text.setPosition(350,0);
        window.draw(text);
        for (int i=0;i<probabilityValues.size();i++){
            stream << probabilityValues[i];
            text.setString(stream.str());
            stream.str(std::string());
            stream.clear();
            text.setPosition(350,35+i*16);
            window.draw(text);
        }
        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))buttonSelected++;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))buttonSelected--;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
                    if (rand()%100<probabilityValues[buttonSelected]){
                        announcementList.addAnnouncement("You hit " + actorAttacking->name + "'s " + bodyPartList[buttonSelected]->name);
                        bodyPartList[buttonSelected]->damage-=totalAttack();
                        if (bodyPartList[buttonSelected]->damage<=0){
                            if (bodyPartList[buttonSelected]->ID == "00"){
                                localItems.push_back(new corpse(actorAttacking->name,actorAttacking->rootPart,actorAttacking->col(),actorAttacking->row(),0,"corpse"));
                                return;
                            }
                            else{
                                localItems.push_back(new limb(bodyPartList[buttonSelected]->name,bodyPartList[buttonSelected]->armor,bodyPartList[buttonSelected]->vanity,actorAttacking->col(),actorAttacking->row(),bodyPartList[buttonSelected]->sprite, bodyPartList[buttonSelected]->attachedParts,0,"limb"));
                            }
                            actorAttacking->rootPart->clearDeadParts(bodyPartList[buttonSelected]);
                        }
                    }
                    else{

                        announcementList.addAnnouncement("You missed " + actorAttacking->name + "'s " + bodyPartList[buttonSelected]->name);
                        actorAttacking->dodgeAttack(this,_map);
                    }
                    return;
                }
            }
        }
        if (buttonSelected == bodyPartList.size())buttonSelected = 0;
        if (buttonSelected == -1)buttonSelected = bodyPartList.size()-1;
        window.display();
    }

}
