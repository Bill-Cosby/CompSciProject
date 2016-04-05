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

    int str = 0, dex=0, intel = 0, acc = 0, def = 0;

    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");
    sf::Text text;
    text.setCharacterSize(12);
    text.setFont(font);

    sf::View characterView(sf::FloatRect(0,0,48,48));
    characterView.setViewport(sf::FloatRect(0.75f,0,0.25f,0.25f));
    std::vector<std::string> questions;
    std::string menuTitles[4] = {"skin colors","hair colors", "eye colors", "hair types"};


    std::string question;
    std::vector<answers> listOfAnswers;

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true)break;


        if (menuSelected == 0)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".skincolor");
        if (menuSelected == 1)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".haircolor");
        if (menuSelected == 2)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".eyecolor");
        if (menuSelected == 3)colors = RSL::unloadColors("data/creatures/creature_standard.raw", character->species+".hairtypes");

        window.clear();
        window.setView(window.getDefaultView());
        text.setCharacterSize(10);
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
            text.setPosition(15+ i*150,30);
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
    char pos = '1';
    int counter = 1;
    answerSelected[0] = 0;
        window.setView(window.getDefaultView());
        keyreleased=false;
    bool answered = false;


    while (true){
        std::string data = character->species + ".Q"+ pos;
        question = (RSL::getStringData("data/creatures/creature_questions.raw",data));
        if (question == "no")break;

        for (int i = 0; i < 10; i ++){
            char temppos = i + '0';
            answers tempString = RSL::getAnswers("data/creatures/creature_questions.raw",character->species+ ".Q"+ pos  + ".A"+ temppos);
            if (tempString.answer != "no")listOfAnswers.push_back(tempString);
        }

        while ( answered == false){
            while (window.pollEvent(event)){
                if (event.type == sf::Event::KeyReleased)keyreleased = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyreleased == true){answerSelected[0]++; keyreleased = false;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyreleased == true){answerSelected[0]--; keyreleased = false;}

            if (answerSelected[0] == listOfAnswers.size())answerSelected[0] = 0;
            if (answerSelected[0] == -1)answerSelected[0] = listOfAnswers.size()-1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true){
                if (listOfAnswers[answerSelected[0]].stat == "strength")str++;
                if (listOfAnswers[answerSelected[0]].stat == "intelligence")intel++;
                if (listOfAnswers[answerSelected[0]].stat == "dexterity")dex++;
                if (listOfAnswers[answerSelected[0]].stat == "defense")def++;
                if (listOfAnswers[answerSelected[0]].stat == "accuracy")acc++;
                answerSelected[0]= 0;
                answered = true;
                keyreleased = false;
            }
            window.clear();
            std::string tempstr;
            std::string formattedQuestion;
            int lineLength = 0, wordLength = 0;
            for (char _c : question){
                tempstr+=_c;
                wordLength+=font.getGlyph(_c,12,false).advance;
                if (_c == ' '){
                    lineLength+=wordLength;
                    if (lineLength + 20 < window.getSize().x){
                        formattedQuestion+= tempstr;
                        tempstr.clear();
                        wordLength = 0;
                    }
                    else{
                        formattedQuestion+= '\n' + tempstr;
                        lineLength = wordLength;
                        wordLength = 0;
                        tempstr.clear();
                    }
                }
            }

            text.setCharacterSize(12);
            text.setString(formattedQuestion);
            text.setPosition(20,30);
            window.draw(text);


            for (int i = 0; i < listOfAnswers.size(); i++){
                std::string tempstr;
                std::string formattedAnswer;
                for (char _c : listOfAnswers[i].answer){
                    tempstr+=_c;
                    wordLength+=font.getGlyph(_c,12/(abs(i-answerSelected[0])+1),false).advance;
                    if (_c == ' ' or _c == ';'){
                        lineLength+=wordLength;
                        if (lineLength + 20 < window.getSize().x){
                            formattedAnswer+= tempstr;
                            tempstr.clear();
                            wordLength = 0;
                        }
                        else{
                            formattedAnswer+= '\n' + tempstr;
                            lineLength = wordLength;
                            wordLength = 0;
                            tempstr.clear();
                        }
                    }
                }

                text.setCharacterSize(12/((abs(i-answerSelected[0])+1)));

                text.setString(formattedAnswer);
                text.setPosition(80,100+i*40);
                window.draw(text);

            }

            window.display();
        }
        listOfAnswers.clear();
        answered = false;
        counter++;
        pos = counter + '0';
    }
    character->attack = RSL::getIntData("data/creatures/creature_standard.raw",character->species+".strength",str);
    character->dexterity = RSL::getIntData("data/creatures/creature_standard.raw",character->species+".dexterity",dex);
    return character;
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
