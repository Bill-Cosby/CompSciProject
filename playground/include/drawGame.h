#ifndef DRAWGAME_H_INCLUDED
#define DRAWGAME_H_INCLUDED
#include "actor.h"
#include "shadowcasting.h"
#include <SFML/Graphics.hpp>

void drawGameworld(std::vector<std::vector<tile*> > &_map, std::vector<actor*> &actors, std::vector<item*> localItems, sf::RenderWindow &window, announcements & announcementList, coordinate &temp, bool &keyrelease, bool &creativeMode);



#endif // DRAWGAME_H_INCLUDED
