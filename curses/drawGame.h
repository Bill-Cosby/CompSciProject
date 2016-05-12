#ifndef DRAWGAME_H_INCLUDED
#define DRAWGAME_H_INCLUDED
#include "actor.h"
#include "light.h"
#include <SFML/Graphics.hpp>

class gameWorld
{

    sf::RectangleShape announcementBorder;
    coordinate startingposition;
    coordinate charplaced;
public:

    void drawGameworld(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, sf::RenderWindow &window, announcements & announcementList, sf::RenderStates &renderState,actor* controlledActor, int, int);
    gameWorld(sf::RenderWindow &window){
        announcementBorder.setFillColor(sf::Color::Black);
        announcementBorder.setOutlineThickness(3);
        announcementBorder.setOutlineColor(sf::Color::White);
        announcementBorder.setSize(sf::Vector2f(window.getSize().x*.40,window.getSize().y*.75));
    }
};





#endif // DRAWGAME_H_INCLUDED
