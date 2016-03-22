#include "actor.h"


bool actor::isItemBetter()
{
    float currentItemStat = 0;
    float newItemStat = 0;
    bool foundItemOfSameType = false;
    newItemStat = itemToPickUp->attack + itemToPickUp->defense + itemToPickUp->health + itemToPickUp->speed + itemToPickUp->value;
    newItemStat /= 5;
    if(equipment.size() == 0)
    {
        return true;
    }
    for(item* _i : equipment){
        if (_i->type == itemToPickUp->type){
            foundItemOfSameType = true;
            currentItemStat = _i->attack + _i->defense + _i->health + _i->speed + _i->value;
            currentItemStat /= 5;
            if(currentItemStat > newItemStat)
            {
                return true;
            }
        }
    }
    if (foundItemOfSameType == false)return true;
    return false;
}

bool actor::canSee(std::vector<std::vector<std::vector<tile*> > > _map, coordinate checkSpot)
{
    int x1=col();
    int y1=row();
    int delta_x(checkSpot.x - x1);
    // if col() == checkSpot.x, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(checkSpot.y - y1);
    // if row() == checkSpot.y, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != checkSpot.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            if (coordinate(x1,y1) == goal)return true;
            if (_map[1][y1][x1]->movementCost==-1 or (_map[1][y1][x1]->isDoor==true and _map[1][y1][x1]->isOpen()==false)){
                return false;
            }
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != checkSpot.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;
            if (coordinate(x1,y1) == goal)return true;
            if (_map[1][y1][x1]->movementCost==-1 or (_map[1][y1][x1]->isDoor==true and _map[1][y1][x1]->isOpen()==false)){
                return false;
            }
        }
    }
    return true;
}

void monster::moveOnPath()
{
    if (path.size()!=0){
        pos(path[path.size()-1].y,path[path.size()-1].x);
        path.erase(path.begin()+path.size()-1);
    }
}
