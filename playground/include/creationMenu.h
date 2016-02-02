#ifndef CREATIONMENU_H_INCLUDED
#define CREATIONMENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "RSL.h"
#include "setTile.h"

int buttonSelected = 0;
int listSelected = 0;

void drawCreationMenu(sf::RenderWindow & window, std::vector<std::vector<std::string> > &lists, bool & keyrelease, coordinate &spawnPoint, std::vector<actor*> &actors, std::vector<std::vector<tile*> > &_map, std::vector<item*> &localItems)
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

    if (keyrelease == true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){listSelected++;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){listSelected--;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){buttonSelected++;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){buttonSelected--;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
            if (listSelected == 0){
                actors.push_back(new monster(lists[0][buttonSelected]));
                actors[actors.size()-1]->pos(spawnPoint.y,spawnPoint.x);
            }
            if (listSelected == 1){
                if (spawnPoint.y>_map.size()-1)_map.resize(spawnPoint.y);
                if (spawnPoint.x>_map[0].size()-1){
                    for (int i = 0;i<_map.size()-1;i++){
                        _map[i].resize((unsigned int)spawnPoint.x);
                        std::cout << i << std::endl;
                    }
                    std::cout << "Here\n";
                }
                std::cout << "Here2\n";
                _map[spawnPoint.y][spawnPoint.x] = NULL;
                std::cout << "Here3\n";
                setTile(_map,lists[1][buttonSelected],spawnPoint);
                std::cout << "Here4\n";
            }
            keyrelease = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){spawnPoint.x++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){spawnPoint.y--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){spawnPoint.y++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){spawnPoint.y++;spawnPoint.x++;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){spawnPoint.y++;spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){spawnPoint.y--;spawnPoint.x--;keyrelease=false;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){spawnPoint.y--;spawnPoint.x++;keyrelease=false;}
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

    window.display();
}

#endif // CREATIONMENU_H_INCLUDED
