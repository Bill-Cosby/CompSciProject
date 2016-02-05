#ifndef CREATIONMENU_H_INCLUDED
#define CREATIONMENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "RSL.h"
#include "setTile.h"
#include "behaviorTree.h"

int buttonSelected = 0;
int listSelected = 0;

void aiCreationMenu(sf::RenderWindow &window, Selector &baseNode)
{
    std::string nodeNames[11] = {"Decorator","Selector","Sequence","Find Path", "Move on path", "Find door", "Open Door", "look for item", "Pick Up Item", "Decide if can attack", "attack"};
    sf::Vector2f offset = sf::Vector2f(0,0);
    int counter = 0;
    bool onButton = false;
    float distancex=0,distancey=0;
    std::vector<compositeNode> nodes;
    nodes.push_back(baseNode);
    sf::FloatRect collision;
    sf::Event event;
    sf::View view(sf::FloatRect(0,0,800,600));
    Node* buttonSelected = NULL;
    float tempx,tempy;
    while (true){
        window.setView(view);
        window.clear();
        if (counter == 2){
            tempx = sf::Mouse::getPosition(window).x, tempy = sf::Mouse::getPosition(window).y;
            counter=0;
        }
        else counter++;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and event.type == sf::Event::MouseMoved){
                distancex = ((tempx-sf::Mouse::getPosition(window).x));
                distancey = ((tempy-sf::Mouse::getPosition(window).y));
            }
            if (event.type == sf::Event::MouseButtonReleased){
                onButton = false;
                buttonSelected = NULL;
                std::cout << "Here\n";
            }
        }
        sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(window);



//        for (compositeNode _R : nodes){
//            if (_R.rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x+offset.x, sf::Mouse::getPosition(window).y+offset.y))){
//                buttonSelected = &_R;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))return;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and buttonSelected != NULL){
                onButton = true;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and buttonSelected != NULL){
                int nodeAdding = 0;
                for (int i = 0;i<11;i++){
                    std::cout << i << ": " << nodeNames[i] << std::endl;
                }
                std::cin >> nodeAdding;
                int parentx = buttonSelected->rect.getPosition().x, parenty = buttonSelected->rect.getPosition().y;
                    switch (nodeAdding){
                    case 0: buttonSelected->addChild(new Decorator(parentx,parenty,"Decorator"));
                            break;
                    case 1: buttonSelected->addChild(new Selector(parentx,parenty,"Selector"));
                            break;
                    case 2: buttonSelected->addChild(new Sequence(parentx,parenty,"Sequence"));
                            break;
                    case 3: buttonSelected->addChild(new findPathNode(parentx,parenty,"Find path"));
                            break;
                    case 4: buttonSelected->addChild(new moveOnPathNode(parentx,parenty,"Move on path"));
                            break;
                    case 5: buttonSelected->addChild(new findDoorNode(parentx,parenty,"Find door"));
                            break;
                    case 6: buttonSelected->addChild(new openDoorNode(parentx,parenty,"Open Door"));
                            break;
                    case 7:buttonSelected->addChild(new lookForItemNode(parentx,parenty,"Look for item"));
                            break;
                    case 8:buttonSelected->addChild(new pickUpItemNode(parentx,parenty,"Pick up item"));
                            break;
                        case 9:buttonSelected->addChild(new decideIfCanAttackNode(parentx,parenty,"Attack decision"));
                            break;
                        case 10:buttonSelected->addChild(new attackNode(parentx,parenty,"attack"));
                            break;
                    default:
                        std::cout << "Not a node\n";
                }
            }
//        }

            std::cout << distancex << "," << distancey << std::endl;

        if (onButton){
            if (buttonSelected!= NULL){
                buttonSelected->rect.move(-distancex,-distancey);
                buttonSelected->linkedFrom.move(-distancex,-distancey);
                buttonSelected->linkedTo.move(-distancex,-distancey);
            }
        }
        else{
            view.move(distancex,distancey);
            offset.x+=distancex;
            offset.y+=distancey;
        }
        buttonSelected = baseNode.Selected(sf::Vector2f(mousepos.x+offset.x, mousepos.y+offset.y));


        distancex = 0;
        distancey = 0;
        baseNode.draw(window);
        window.display();

    }
}

void drawCreationMenu(sf::RenderWindow & window, std::vector<std::vector<std::string> > &lists, bool & keyrelease, coordinate &spawnPoint, std::vector<actor*> &actors, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems, bool & creativeMode, Selector &baseNode)
{
    std::string titles[3] = {"actors","tiles","items"};

    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")){
        std::cout << "Font error\n";
    }


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);

    while (keyrelease == true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){listSelected++;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){listSelected--;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){buttonSelected++;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){buttonSelected--;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
            if (listSelected == 0){
                actors.push_back(new monster(lists[0][buttonSelected]));
                actors[actors.size()-1]->pos(spawnPoint.y,spawnPoint.x);
                actors[actors.size()-1]->sprite.setPosition(spawnPoint.x*16,spawnPoint.y*16);
            }
            if (listSelected == 1){
                if (spawnPoint.y>_map.size()-1)_map.resize(spawnPoint.y);
                if (spawnPoint.x>_map[0].size()-1){
                    for (int i = 0;i<_map.size()-1;i++){
                        _map[i].resize((unsigned int)spawnPoint.x);
                    }
                }
                _map[spawnPoint.y][spawnPoint.x] = NULL;
                setTile(_map,lists[1][buttonSelected],spawnPoint);
            }
            keyrelease = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            creativeMode = false;
            keyrelease = false;
            for (actor* _a : actors){
                if (coordinate(_a->col(),_a->row()) == spawnPoint){_a->controlled = true;return;}
            }

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){spawnPoint.x++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){spawnPoint.y--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){spawnPoint.y++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){spawnPoint.y++;spawnPoint.x++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){spawnPoint.y++;spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){spawnPoint.y--;spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){spawnPoint.y--;spawnPoint.x++;keyrelease=false;}

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){aiCreationMenu(window,baseNode);keyrelease = false;}
    }

    if (listSelected < 0)listSelected = 2;
    if (listSelected == 3) listSelected = 0;
    if (buttonSelected < 0)buttonSelected = lists[listSelected].size()-1;
    if (buttonSelected == lists[listSelected].size()) buttonSelected = 0;

    for (int i=0;i<3;i++){
        if (listSelected == i){
            text.setStyle(sf::Text::Underlined);
        }
        text.setPosition(550 + (70*i+1), 20);
        text.setString(titles[i]);
        window.draw(text);
        text.setStyle(sf::Text::Regular);
    }

    for (int i = 0;i < lists[listSelected].size(); i++){
        if (i == buttonSelected){
            text.setStyle(sf::Text::Underlined);
        }
        text.setPosition(550,25+(15*(i+1)));
        text.setString(lists[listSelected][i]);
        window.draw(text);
        text.setStyle(sf::Text::Regular);
    }

}

#endif // CREATIONMENU_H_INCLUDED
