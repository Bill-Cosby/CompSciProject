#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "actor.h"
#include "tile.h"



class custom_menu
{
protected:
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    bool verticle;
    bool buttonSelected;
    int percentOfScreen;
};

class mainMenu : custom_menu
{
public:
    bool quit_game;
    mainMenu(std::string,bool, int);
};

actor* characterCreationMenu(sf::RenderWindow &window);
