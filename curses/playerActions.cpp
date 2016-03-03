#include "actor.h"

void player::movement(std::vector<std::vector<tile*> > &_map,std::vector<item*> &localItems, std::vector<actor*> &actors, sf::RenderWindow &window, bool &keyrelease, announcements & announcementList)
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
    while (counter>=customSpeed and keyrelease == true){

            while (pressedKey == false){
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::KeyPressed){
                        pressedKey = true;
                    }
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
                            pressedKey = true;
                        }
                    }
                }
                _map[temp.y][temp.x]->interactWithDoor(false);
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
            else if (_map[temp.y][temp.x]->movementCost>-100){
                if (_map[temp.y][temp.x]->isDoor){
                    moveThroughDoor = _map[temp.y][temp.x]->interactWithDoor(true);
                }
                if (moveThroughDoor == true){
                    pos(temp.y,temp.x);
                    counter=0;
                }
            }


        sprite.setPosition(x*16,y*16);
    }
    counter++;
}

void player::attackEnemy(std::vector<std::vector<tile*> >& _map, announcements& announcementList, std::vector<item*> &localItems, sf::RenderWindow &window)
{
    if (actorAttacking==NULL)return;
    int temp;
    int buttonSelected = 0;

    std::vector<int> attackValues;
    std::vector<int> probabilityValues;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);

    std::vector<bodyPart*> bodyPartList = actorAttacking->rootPart->returnParts(bodyPartList);

    for (bodyPart* _b : bodyPartList){
        std::cout << _b->weight - attack << std::endl;
        if (_b->armor !=NULL)temp = (_b->armor->defense + _b->weight) - attack;
        else temp = (_b->weight - attack);
        if (temp < 0){
            temp = 0;
        }
        attackValues.push_back(temp);
        probabilityValues.push_back(rand()%actorAttacking->totalWeight);
        std::cout << _b << std::endl;
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))buttonSelected--;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
                    bodyPartList[buttonSelected]->damage-=attackValues[buttonSelected];
                    return;
                }
            }
        }
        if (buttonSelected == bodyPartList.size())buttonSelected = 0;
        if (buttonSelected < 0)buttonSelected = bodyPartList.size()-1;
        window.display();
    }

}
