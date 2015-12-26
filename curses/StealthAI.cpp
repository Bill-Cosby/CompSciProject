#include "StealthAI.h"

void StealthAI(coordinate goal, monster* playerEvaluating, std::vector<actor*> actors, std::vector<std::vector<tile> > _map)
{
    bool canBeSeen=false;
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

                if (_c == coordinate(actors[i]->col(),actors[i]->row()))
                {
                    continue;
                }
                playerEvaluating->badPosition.push_back(coordinate(actors[i]->col(),actors[i]->row()));
            }


            if (playerEvaluating->canSee(_map,coordinate(actors[i]->col(),actors[i]->row()))){
                playerEvaluating->memory=coordinate(actors[i]->col(),actors[i]->row());
                canBeSeen=true;
                playerEvaluating->hidden=false;
            }
        }
        if (playerEvaluating->memory!=goal){
            playerEvaluating->getPath(_map,goal,playerEvaluating->noGo);
            playerEvaluating->memory=goal;
        }

        if (canBeSeen==false){
            playerEvaluating->moveOnPath(_map);

        }
        playerEvaluating->counter=0;
        playerEvaluating->badPosition.clear();
    }
    else{
        playerEvaluating->counter++;
    }
}
