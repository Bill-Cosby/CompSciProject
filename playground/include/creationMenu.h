#ifndef CREATIONMENU_H_INCLUDED
#define CREATIONMENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "RSL.h"

int buttonSelected = 0;
int listSelected = 0;

void drawCreationMenu(sf::RenderWindow & window, std::vector<std::vector<std::string> > &lists, bool & keyrelease)
{
    window.setView(window.getDefaultView());
    std::string titles[3] = {"actors","tiles","items"};


    sf::Event event;

    sf::Font font;
    if (!font.loadFromFile("data/PressStart2P-Regular.ttf")){
        std::cout << "Font error\n";
    }


    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);

    window.clear();
    if (keyrelease == true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)){listSelected++;keyrelease = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)){listSelected--;keyrelease = false;}
    }

    if (listSelected < 0)listSelected = 2;
    if (listSelected == 3) listSelected = 0;

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
        text.setPosition(550,25+(15*(i+1)));
        text.setString(lists[listSelected][i]);
        window.draw(text);
    }

    window.display();
}

#endif // CREATIONMENU_H_INCLUDED
