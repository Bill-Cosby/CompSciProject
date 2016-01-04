#ifndef DRAWGAME_H_INCLUDED
#define DRAWGAME_H_INCLUDED
#include "actor.h"


void drawGameworld(std::vector<std::vector<tile*> > _map, std::vector<actor*> *actors, std::vector<item*> localItems, screen *scr);

#endif // DRAWGAME_H_INCLUDED
