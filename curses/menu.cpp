#include "menu.h"

actor* characterCreationMenu(sf::RenderWindow &window)
{
    tile* exampleScreen[3][3] = {{new tile(grass,0,"grass"),new tile(grass,0,"grass"),new tile(grass,0,"grass")},
                                 {new tile(grass,0,"grass"),new tile(grass,0,"grass"),new tile(grass,0,"grass")},
                                 {new tile(grass,0,"grass"),new tile(grass,0,"grass"),new tile(grass,0,"grass")},};

    for (int y = 0;y<3;y++){
        for (int x = 0;x<3;x++){
            exampleScreen[y][x]->position = coordinate(x,y);
        }
    }

    bool pickedSpecies = false, keyreleased = false;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setFont(font);

    sf::View characterView(sf::FloatRect(0,0,48,48));
    characterView.setViewport(sf::FloatRect(0.75f,0,0.25f,0.25f));
    std::vector<std::string> questions;
    std::vector<std::vector<std::string> > answers;

    int answerSelected = 0;
    sf::RenderStates renderState;

    actor* character;

    sf::Event event;

    std::vector<std::string>species = RSL::getSpecies("data/creatures/creature_standard.raw","name");

    while (true)
    {

        while (pickedSpecies == false){
            window.clear();
            text.setCharacterSize(20);
            text.setString("Of what species were you born?");
            text.setPosition(100,20);
            window.draw(text);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyreleased == true){answerSelected++; keyreleased = false;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyreleased == true){answerSelected--; keyreleased = false;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true){character = new player(species[answerSelected]); keyreleased = false;pickedSpecies = true;}

            if (answerSelected==-1)answerSelected = species.size()-1;
            if (answerSelected == species.size())answerSelected = 0;

            while (window.pollEvent(event)){
                if (event.type == sf::Event::KeyReleased)keyreleased = true;
            }

            for (int i = 0;i < species.size(); i++){
                text.setCharacterSize(20/((abs(i-answerSelected)+1)));
                text.setString(species[i]);
                text.setPosition(100,100+i*40);
                window.draw(text);
            }

            window.display();
        }

        window.setView(characterView);
        window.clear();
        for (int y=0;y<3;y++){
            for (int x=0;x<3;x++){
                //exampleScreen[y][x]->drawTile(window,renderState);
            }
        }
        character->drawActor(window);
        window.display();
    }

}
