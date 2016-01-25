#include "actor.h"

void player::openInventory(sf::RenderWindow &window, std::vector<item*> *localItems)
{
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

    bool keyrelease = true;

    item* itemLookingAt;

    sf::Event event;

    int itemSelected = 0;
    int buttonSelected = 0;

    std::cout << "Here\n";

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


        titleText.setString(itemLookingAt->name);
        titleText.setPosition(descriptionWindow.getPosition().x+4, 4);
        window.draw(titleText);

        menuText.setString(itemLookingAt->itemDescription());
        menuText.setPosition(descriptionWindow.getPosition().x+4,24);
        window.draw(menuText);

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyrelease == true and examiningItem == false){
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyrelease == true and examiningItem == false){
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
                        equipment.push_back(itemLookingAt);
                        inventory.erase(inventory.begin()+itemSelected);
                        itemSelected = equipment.size()-1;
                    }
                    activeWindow = 1 - activeWindow;
                }
                if (buttonSelected == 1){
                    itemLookingAt->x = x;
                    itemLookingAt->y = y;
                    localItems->push_back(itemLookingAt);
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
            }
            else{
                buttonSelected = 1 - buttonSelected;
            }
            keyrelease = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) and keyrelease == true){
            if (examiningItem == false){
                activeWindow = 1-activeWindow;
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
    window.clear();
}

void player::examineGround(sf::RenderWindow &window, std::vector<item*> *itemsExamining,coordinate spotExamining)
{

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    sf::Text menuItem;
    menuItem.setFont(font);
    menuItem.setCharacterSize(12);

    sf::RectangleShape itemList;
    sf::RectangleShape descriptionWindow;

    itemList.setSize(sf::Vector2f(100,window.getSize().y/2));
    descriptionWindow.setSize(sf::Vector2f(100,window.getSize().y/2-1));

    itemList.setPosition(window.getSize().x-100,1);
    descriptionWindow.setPosition(window.getSize().x-100,window.getSize().y/2+1);

    itemList.setOutlineThickness(3);
    descriptionWindow.setOutlineThickness(3);

    itemList.setOutlineColor(sf::Color::White);
    descriptionWindow.setOutlineColor(sf::Color::White);

    std::vector<item*> itemsYouFound;
    int itemExamining = 0;
    char ch;
    bool examiningGround=true;
    bool unloadedItem=false;
    for (int i=0;i<(*itemsExamining).size();i++){
        if (coordinate(((*itemsExamining)[i]->x),(*itemsExamining)[i]->y)==spotExamining){
            itemsYouFound.push_back((*itemsExamining)[i]);
        }
    }

    while (true){
        for (int i=0;i<itemsYouFound.size();i++){
            if (itemsYouFound.size()>itemList.getSize().y){
                break;
            }
            else{
                menuItem.setPosition(itemList.getPosition().x+4,18+(12*i));
                if (itemsYouFound[i]->selected == false){
                    menuItem.setString("-");
                }
                else{
                    menuItem.setString("+");
                }
                window.draw(menuItem);
                if (i == itemExamining){
                    menuItem.setStyle(sf::Text::Underlined);
                }
                menuItem.setString(itemsYouFound[itemExamining]->name);
                window.draw(menuItem);
            }
        }
    }


//    touchwin(scr->subwindow.examineWindow);
//    wborder(scr->subwindow.examineWindow,0,0,0,0,0,0,0,0);
//    std::vector<item*> itemsYouFound;
//    char ch;
//    bool examiningGround=true;
//    bool unloadedItem=false;
//    for (int i=0;i<(*itemsExamining).size();i++){
//        if (coordinate(((*itemsExamining)[i]->x),(*itemsExamining)[i]->y)==spotExamining){
//            itemsYouFound.push_back((*itemsExamining)[i]);
//        }
//    }
//    int itemSelected=0;
//
//    while (examiningGround==true){
//        for (int i=0;i<scr->subwindow.height();i++){
//
//            if (i==itemsYouFound.size()){
//                break;
//            }
//            if (itemsYouFound[i]->selected==false){
//                mvwaddch(scr->subwindow.examineWindow,i+1,1,'-');
//            }
//            else{
//                mvwaddch(scr->subwindow.examineWindow,i+1,1,'+');
//            }
//            if (i == itemSelected){
//                wattron(scr->subwindow.examineWindow,A_REVERSE);
//            }
//            mvwaddstr(scr->subwindow.examineWindow,i+1,2,itemsYouFound[i]->name.c_str());
//            wattroff(scr->subwindow.examineWindow,A_REVERSE);
//        }
//        wrefresh(scr->subwindow.examineWindow);
//        ch=wgetch(scr->subwindow.examineWindow);
//        for (int i=0;i<numberOfControls;i++){
//            if (ch==numpadControls[i] or ch==VIKEYSControls[i] or ch==keyBrdControls[i]){
//                if (i==0){
//                   if (itemSelected-1>=0){
//                        itemSelected--;
//                    }
//                }
//                else if (i==2){
//                    if (itemSelected+1<itemsYouFound.size()){
//                        itemSelected++;
//                    }
//                }
//                else if (i==3){
//                    itemsYouFound[itemSelected]->selected=true;
//                }
//                else if (i==4){
//                    itemsYouFound[itemSelected]->selected=false;
//                }
//                else if (i==12){
//                    examiningGround=false;
//                }
//                else if (i==15){
//                    int wait=0;
//                    int temp=itemsYouFound.size();
//                    while (true){
//                        unloadedItem=false;
//                        for (int j=0;j<itemsYouFound.size();j++){
//                            if (itemsYouFound[j]->selected==true){
//                                itemsYouFound[j]->selected=false;
//                                inventory.push_back((*itemsExamining)[j]);
//                                std::string temporary = "You picked up " + (*itemsExamining)[j]->name;
//                                for (int k = 0; k < (*itemsExamining).size(); k++){
//                                    if ((*itemsExamining)[k]==itemsYouFound[j]){
//                                        (*itemsExamining).erase((*itemsExamining).begin()+k);
//                                    }
//                                }
//                                scr->addAnnouncement(temporary);
//                            }
//                            wait++;
//                        }
//                        if (wait==temp){
//                            break;
//                        }
//                    }
//                    clear();
//                    werase(scr->subwindow.examineWindow);
//                    wrefresh(scr->subwindow.examineWindow);
//                    bool youAintRight=false;
//
//                    return;
//                }
//            }
//        }
//    }
}

