#include "RSL.h"

namespace RSL
{
    void setupMenu(std::string fileName, sf::RenderWindow &window)
    {

        sf::Font font;
        font.loadFromFile("data/PressStart2P-Regular.ttf");

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(12);

        std::vector<menu_button> listOfButtons;
        std::string menuTitle = RSL::getStringData(fileName, "title");
        sf::Event event;
        std::cout << menuTitle << std::endl;
        while (window.isOpen()){
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }
            listOfButtons = getButtons(fileName);
            for (menu_button _b : listOfButtons){
                text.setPosition(_b.x,_b.y);
                text.setString(_b.name);
                window.draw(text);
            }
            window.display();
        }

    }
}
