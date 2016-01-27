#include "StealthAI.h"

void StealthAI(coordinate goal, monster* playerEvaluating, std::vector<actor*> actors, std::vector<std::vector<tile*> > _map)
{
    if (playerEvaluating->hidden==false){
        playerEvaluating->sprinting=true;
    }
    if (goal==coordinate(playerEvaluating->col(),playerEvaluating->row())){
        return;
    }
    if (playerEvaluating->getCounter()==playerEvaluating->getSpeed()){

        for(int i=1;i<actors.size();i++){

            if (playerEvaluating->badPosition.size()==0){
                playerEvaluating->badPosition.push_back(coordinate(actors[i]->col(),actors[i]->row()));
            }
            for (coordinate _c : playerEvaluating->badPosition){

                if (_c == coordinate(actors[i]->col(),actors[i]->row())){
                    continue;
                }
                playerEvaluating->badPosition.push_back(coordinate(actors[i]->col(),actors[i]->row()));
            }


            if (playerEvaluating->canSee(_map,coordinate(actors[i]->col(),actors[i]->row())) and playerEvaluating->hidden==true){

                monster* pieceOfShit = dynamic_cast<monster*>(actors[i]);
                //playerEvaluating->getPath(_map,StealthAI_hide(playerEvaluating,pieceOfShit,_map),playerEvaluating->noGo);

                playerEvaluating->memory=coordinate(actors[i]->col(),actors[i]->row());
                playerEvaluating->hidden=false;
            }
        }

        if (playerEvaluating->memory!=goal){

            playerEvaluating->getPath(_map,goal,playerEvaluating->noGo);
            playerEvaluating->memory=goal;
        }

        playerEvaluating->moveOnPath(_map);
        playerEvaluating->counter=0;
        playerEvaluating->badPosition.clear();
    }
    else{
        playerEvaluating->counter++;
    }
}

coordinate StealthAI_hide(monster* playerEvaluating, monster* monsterThatCaughtYou , std::vector<std::vector<tile*> > _map)
{
    bool foundHidingSpot=false;
    std::vector<tile*> frontier;

    frontier.push_back(_map[playerEvaluating->row()][playerEvaluating->col()]);
    tile* fuckDamionALot=_map[playerEvaluating->row()][playerEvaluating->col()];

    while (foundHidingSpot==false){
        for (int i=0;i<frontier.size();i++){
            for (int y=-1;y<2;y++){
                for (int x=-1;x<2;x++){
                    frontier.push_back(_map[frontier[i]->position.y+y][frontier[i]->position.x+x]);
                }
            }
            if (!monsterThatCaughtYou->canSee(_map,frontier[i]->position)){
                return frontier[i]->position;
            }
        }
    }
}
