#include "actor.h"

void player::openInventory(sf::RenderWindow &window, std::vector<item*> &localItems, bool & keyrelease)
{
    window.setView(window.getDefaultView());
    std::vector<bodyPart*> bodyPartsToEquipIn;
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    sf::Text titleText;
    sf::Text menuText;

    titleText.setFont(font);
    menuText.setFont(font);

    titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    titleText.setCharacterSize(18);
    menuText.setCharacterSize(12);

    sf::RectangleShape inventoryBlock(sf::Vector2f(window.getSize().x*.25, window.getSize().y*.75));
    sf::RectangleShape equipmentBlock(sf::Vector2f(window.getSize().x*.25, window.getSize().y*.75));
    sf::RectangleShape descriptionWindow(sf::Vector2f(window.getSize().x*.50, window.getSize().y*.50));

    inventoryBlock.setPosition(1,1);
    equipmentBlock.setPosition(window.getSize().x*.25+1,1);
    descriptionWindow.setPosition(window.getSize().x*.50+4,1);

    inventoryBlock.setFillColor(sf::Color::Black);
    equipmentBlock.setFillColor(sf::Color::Black);
    descriptionWindow.setFillColor(sf::Color::Black);

    inventoryBlock.setOutlineThickness(3);
    equipmentBlock.setOutlineThickness(3);
    descriptionWindow.setOutlineThickness(3);

    inventoryBlock.setOutlineColor(sf::Color::White);
    equipmentBlock.setOutlineColor(sf::Color::White);
    descriptionWindow.setOutlineColor(sf::Color::White);

    bool activeWindow=0;

    bool examiningItem = false;
    bool inventoryOpen = true;

    item* itemLookingAt = NULL;

    sf::Event event;

    int itemSelected = 0;
    int buttonSelected = 0;

    while (true){

        window.clear();
        window.draw(inventoryBlock);
        window.draw(equipmentBlock);
        window.draw(descriptionWindow);

        titleText.setString("inventory");
        titleText.setPosition(3,4);
        window.draw(titleText);

        titleText.setString("equipment");
        titleText.setPosition((window.getSize().x*.25+3),4);
        window.draw(titleText);


            for (int i = 0; i < inventory.size(); i++){
                if (i == itemSelected and activeWindow == 0){
                    menuText.setStyle(sf::Text::Underlined);
                    itemLookingAt = inventory[i];
                }
                for (char _c : itemLookingAt->name){

                }
                menuText.setString(inventory[i]->name);
                menuText.setPosition(inventoryBlock.getPosition().x+4,22+(4+(i*menuText.getCharacterSize())));
                window.draw(menuText);

                menuText.setStyle(sf::Text::Regular);
            }

            for (int i = 0; i < equipment.size(); i++){
                if (i == itemSelected and activeWindow == 1){
                    menuText.setStyle(sf::Text::Underlined);
                    itemLookingAt = equipment[i];
                }
                menuText.setString(equipment[i]->name);
                menuText.setPosition(equipmentBlock.getPosition().x+4,22+(4+(i*menuText.getCharacterSize())));
                window.draw(menuText);

                menuText.setStyle(sf::Text::Regular);
            }

        if (itemLookingAt != NULL){
                int lineLength=0;
                int wordLength=0;

                std::string formattedDesc;
                std::string tempStr;
            titleText.setString(itemLookingAt->name);
            titleText.setPosition(descriptionWindow.getPosition().x+4, 4);
            window.draw(titleText);
            for (char _c : itemLookingAt->itemDescription()){
                tempStr+=_c;
                wordLength+=font.getGlyph(_c,12,false).advance;
                if (_c == ' '){
                    lineLength+=wordLength;
                    if (lineLength + descriptionWindow.getPosition().x + 4 < window.getSize().x){
                        formattedDesc+= tempStr;
                        tempStr.clear();
                        wordLength = 0;
                    }
                    else{
                        formattedDesc+= '\n' + tempStr;
                        lineLength = wordLength;
                        wordLength = 0;
                        tempStr.clear();
                    }
                }
            }
            menuText.setString(formattedDesc);
            menuText.setPosition(descriptionWindow.getPosition().x+4,24);
            window.draw(menuText);
        }


        if (examiningItem == true and buttonSelected == 0){
            menuText.setStyle(sf::Text::Underlined);
        }
        if (activeWindow == 0)menuText.setString("equip");
        else menuText.setString("unequip");
        menuText.setPosition(descriptionWindow.getPosition().x+10,descriptionWindow.getSize().y-15);
        window.draw(menuText);

        menuText.setStyle(sf::Text::Regular);

        if (examiningItem == true and buttonSelected == 1){
            menuText.setStyle( sf::Text::Underlined);
        }
        menuText.setString("drop");
        menuText.setPosition(descriptionWindow.getPosition().x+100,descriptionWindow.getSize().y-15);
        window.draw (menuText);

        menuText.setStyle(sf::Text::Regular);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyrelease == true and examiningItem == false){
            if (activeWindow == 0){
                if (itemSelected+1 >= inventory.size()) itemSelected = 0;
                else itemSelected++;
            }
            if (activeWindow == 1){
                if (itemSelected+1 >= equipment.size()) itemSelected = 0;
                else itemSelected++;
            }
            keyrelease = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyrelease == true and examiningItem == false){
            if (activeWindow == 0){
                if (itemSelected-1 < 0) itemSelected = inventory.size()-1;
                else itemSelected--;
            }
            if (activeWindow == 1){
                if (itemSelected-1 < 0) itemSelected = equipment.size()-1;
                else itemSelected--;
            }
            keyrelease = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyrelease == true){
            if (examiningItem == false)examiningItem = true;
            else{
                if (buttonSelected == 0){
                    if (itemLookingAt->equipped == true){
                            itemLookingAt->equipped = false;
                        inventory.push_back(itemLookingAt);
                        equipment.erase(equipment.begin()+itemSelected);
                        itemSelected = inventory.size()-1;
                    }
                    else{
                        itemLookingAt->equipped = true;
                        itemToPickUp = itemLookingAt;
                        equipItem(localItems);

                        rootPart->findItem(itemLookingAt,true);
                        equipment.push_back(itemLookingAt);
                        inventory.erase(inventory.begin()+itemSelected);
                        itemSelected = equipment.size()-1;
                    }
                    activeWindow = 1 - activeWindow;
                }
                if (buttonSelected == 1){

                    itemLookingAt->x = x;
                    itemLookingAt->y = y;

                    itemLookingAt->sprite.setPosition(x*16,y*16);
                    itemLookingAt->selected = false;

                    localItems.push_back(itemLookingAt);
                    if (activeWindow == 0)inventory.erase(inventory.begin()+itemSelected);
                    if (activeWindow == 1)equipment.erase(equipment.begin()+itemSelected);
                }
                examiningItem = false;
            }
            keyrelease = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) and keyrelease == true){
            if (examiningItem==true){examiningItem = false;keyrelease=false;}
            else break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) and keyrelease == true){
            if (examiningItem == false){
                activeWindow = 1-activeWindow;
                itemSelected = 0;
                itemLookingAt = NULL;
            }
            else{
                buttonSelected = 1 - buttonSelected;
            }
            keyrelease = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) and keyrelease == true){
            if (examiningItem == false){
                activeWindow = 1-activeWindow;
                itemSelected = 0;
                itemLookingAt = NULL;
            }
            else{
                buttonSelected = 1 - buttonSelected;
            }
            keyrelease = false;
        }

        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }


        window.display();
    }
    std::cout << "Here\n";
    window.clear();
}

void player::examineGround(sf::RenderWindow &window, std::vector<item*> &itemsExamining,coordinate spotExamining, announcements & announcementList, tile* &tempTile)
{
    window.setView(window.getDefaultView());
    sf::Event event;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    sf::Text menuItem;
    menuItem.setFont(font);
    menuItem.setCharacterSize(12);

    sf::RectangleShape itemList;
    sf::RectangleShape descriptionWindow;

    itemList.setSize(sf::Vector2f(300,window.getSize().y/2));
    descriptionWindow.setSize(sf::Vector2f(300,window.getSize().y/2-1));

    itemList.setPosition(window.getSize().x-300,1);
    descriptionWindow.setPosition(window.getSize().x-300,window.getSize().y/2+1);

    itemList.setFillColor(sf::Color::Black);
    descriptionWindow.setFillColor(sf::Color::Black);

    itemList.setOutlineThickness(3);
    descriptionWindow.setOutlineThickness(3);

    itemList.setOutlineColor(sf::Color::White);
    descriptionWindow.setOutlineColor(sf::Color::White);

    std::vector<item*> itemsYouFound;
    int itemExamining = 0;
    char ch;
    bool examiningGround=true;
    bool unloadedItem=false;
    bool keyrelease = false;
    for (int i=0;i<itemsExamining.size();i++){
        if (coordinate((itemsExamining[i]->x),itemsExamining[i]->y)==spotExamining){
            itemsYouFound.push_back(itemsExamining[i]);
        }
    }
    if (tempTile!=NULL){
        std::vector<item*> tempItems = tempTile->openContainer();
        std::cout << tempItems.size() << std::endl;
        for (item* _i : tempItems){
                std::cout << _i->name << std::endl;
            itemsYouFound.push_back(_i);
        }
    }

    while (true){
        window.clear();
        window.draw(itemList);
        window.draw(descriptionWindow);
        for (int i=0;i<itemsYouFound.size();i++){
            if (itemsYouFound.size()>itemList.getSize().y){
                break;
            }
            else{
                menuItem.setPosition(itemList.getPosition().x+4,18+(20*i));
                if (itemsYouFound[i]->selected == false){
                    menuItem.setString("-");
                }
                else{
                    menuItem.setString("+");
                }
                window.draw(menuItem);
                menuItem.setPosition(itemList.getPosition().x+20,18+(20*i));
                if (i == itemExamining){
                    menuItem.setStyle(sf::Text::Underlined);
                }
                menuItem.setString(itemsYouFound[i]->name);
                window.draw(menuItem);
                menuItem.setStyle(sf::Text::Regular);
            }
        }
        window.display();

        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyReleased){
                keyrelease = true;
            }
        }
        if (itemsYouFound.size()>=0){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyrelease == true){itemExamining--;keyrelease = false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyrelease == true){itemExamining++;keyrelease = false;}

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) and keyrelease == true){itemsYouFound[itemExamining]->selected = true;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) and keyrelease == true){itemsYouFound[itemExamining]->selected = false;}

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyrelease == true){
                int wait=0;
                int temp=itemsYouFound.size();
                while (true){
                    unloadedItem=false;
                    for (int j=0;j<itemsYouFound.size();j++){
                        if (itemsYouFound[j]->selected==true){
                            itemsYouFound[j]->selected=false;
                            inventory.push_back(itemsYouFound[j]);
                            std::cout << itemsYouFound[j]->name << std::endl;
                            std::string temporary = "You picked up " + itemsYouFound[j]->name;

                            announcementList.addAnnouncement(temporary);
                            for (int k = 0; k < itemsExamining.size(); k++){
                                if (itemsExamining[k]==itemsYouFound[j]){
                                    itemsExamining.erase(itemsExamining.begin()+k);
                                }
                            }
                        }
                        wait++;
                    }
                    if (wait==temp){
                        break;
                    }
                }
                return;
            }
            if (itemExamining==itemsYouFound.size())itemExamining=0;
            if (itemExamining==-1)itemExamining = itemsYouFound.size()-1;
        }
    }
}

