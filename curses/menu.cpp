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
    bool pickedSpecies = false, keyreleased = true;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setCharacterSize(12);
    text.setFont(font);

    sf::View characterView(sf::FloatRect(0,0,48,48));
    characterView.setViewport(sf::FloatRect(0.75f,0,0.25f,0.25f));
    std::vector<std::string> questions;
    std::string menuTitles[4] = {"skin colors","hair colors", "eye colors", "hair types"};
    std::vector<std::vector<std::string> > answers;

    int answerSelected[4] = {0,0,0,0}, menuSelected = 0;
    sf::RenderStates renderState;

    actor* character;

    sf::Event event;

    std::vector<std::string> colors;

    while (true)
    {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::KeyReleased)keyreleased = true;
        }
        if (pickedSpecies == false){
            character = speciesChoiceMenu(window);
            pickedSpecies = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyreleased == true){answerSelected[menuSelected]++; keyreleased = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyreleased == true){answerSelected[menuSelected]--; keyreleased = false;}

        if (answerSelected[menuSelected] == colors.size())answerSelected[menuSelected] = 0;
        if (answerSelected[menuSelected] == -1)answerSelected[menuSelected] = colors.size()-1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) and keyreleased == true and menuSelected-1 !=-1){menuSelected--; keyreleased = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) and keyreleased == true and menuSelected+1 != 4){menuSelected++; keyreleased = false;}


        if (menuSelected == 0)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".skincolor");
        if (menuSelected == 1)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".haircolor");
        if (menuSelected == 2)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".eyecolor");
        if (menuSelected == 3)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".hairtypes");

        window.clear();
        window.setView(window.getDefaultView());
        text.setCharacterSize(8);
        for (int i = 0; i < 4; i++){
            if (i == menuSelected){
                text.setStyle(sf::Text::Underlined);
                if (i == 0)character->rootPart->setColors(giveColor(colors[answerSelected[menuSelected]]),false,false);
                if (i == 1)character->rootPart->setColors(giveColor(colors[answerSelected[menuSelected]]),true,false);
                if (i == 2)character->rootPart->setColors(giveColor(colors[answerSelected[menuSelected]]+"Eye"),false,true);
                if (i == 3){
                    sf::Texture tempTex = RSL::getTextureData("data/textures/hair.raw",colors[answerSelected[menuSelected]]+".texture");
                    character->rootPart->setHair(tempTex);
                }
            }
            text.setString(menuTitles[i]);
            text.setPosition(15+ i*100,30);
            window.draw(text);
            text.setStyle(sf::Text::Regular);
        }

        for (int i = 0; i < colors.size(); i++){

                text.setCharacterSize(20/((abs(i-answerSelected[menuSelected])+1)));

                text.setString(colors[i]);
                text.setPosition(100,100+i*40);
                window.draw(text);
        }

        window.setView(characterView);
        for (int y=0;y<3;y++){
            for (int x=0;x<3;x++){
                exampleScreen[y][x]->drawTile(window,renderState);
            }
        }
        character->drawActor(window);
        window.display();
    }
}

actor* speciesChoiceMenu(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    actor* character;
    bool keyreleased= true;
    int answerSelected = 0;
    sf::Event event;

    std::vector<std::string>species = RSL::getSpecies("data/creatures/creature_standard.raw","name");
    while (true){
            window.clear();
            text.setCharacterSize(20);
            text.setString("Of what species were you born?");
            text.setPosition(100,20);
            window.draw(text);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyreleased == true){answerSelected++; keyreleased = false;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyreleased == true){answerSelected--; keyreleased = false;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true){
                character = new player(species[answerSelected]);
                keyreleased = false;
                character->pos(1,1);
                return character;
            }

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
}
