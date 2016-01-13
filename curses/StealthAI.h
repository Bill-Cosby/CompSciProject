#ifndef STEALTHAI_H_INCLUDED
#define STEALTHAI_H_INCLUDED

#include "aStar.h"
#include "actor.h"

void StealthAI(coordinate goal, monster* playerEvaluating, std::vector<actor*> actors, std::vector<std::vector<tile> > _map);

coordinate StealthAI_hide(monster* playerEvaluating, monster* monsterThatCaughtYou, std::vector<std::vector<tile> > _map);

#endif // STEALTHAI_H_INCLUDED
