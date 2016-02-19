#include "actor.h"



bool monster::canSee(std::vector<std::vector<tile*> > _map, coordinate checkSpot)
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
            if (_map[y1][x1]->movementCost==-1 or (_map[y1][x1]->isDoor==true and _map[y1][x1]->isOpen()==false)){
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
            if (_map[y1][x1]->movementCost==-1 or (_map[y1][x1]->isDoor==true and _map[y1][x1]->isOpen()==false)){
                return false;
            }
        }
    }
    return true;
}

void monster::movement(std::vector<std::vector<tile*> > &_map,std::vector<item*> &localItems, std::vector<actor*> &actors,  sf::RenderWindow &window, bool &keyrelease, announcements & announcementList)
{

    //initialize the goal to not be used
    coordinate goal(-1,-1);

    //raise the monster's counter by 1
    counter++;

    //we aren't initially attacking anything (stateless AI)
    bool attacking=false;

    //not currently used until we find a better method
    std::vector<coordinate> noGo;

    //if you're evil and you see someone of a different species, they're your target
    for (actor* _a : actors){
        noGo.push_back(coordinate(_a->col(),_a->row()));
        if (EVIL==true and species!=_a->species and canSee(_map,coordinate(_a->col(),_a->row()))){
            goal = coordinate(_a->col(),_a->row());
            memory=goal;
        }
    }

    // if you can see your goal, make a path to it.
    if (canSee(_map,goal))
    {
        path = pathFinder(_map,coordinate(col(),row()),goal,noGo);
    }



    //to actually commence AI movement and things:
    if (counter==5){//if there's no path:

        if (path.size()== 0)
        {

            //if you have no memory:
            if (memory.x!=-1 and memory.y!=-1)
            {
                path=pathFinder(_map,coordinate(col(),row()),memory,noGo);
                memory=coordinate(-1,-1);
            }

            //if your position isn't your post and you have a post
            else if (coordinate(x,y) != post and post!=coordinate(-1,-1)){
                path=pathFinder(_map,coordinate(col(),row()),post,noGo);
            }
        }
        //if you have a path:
        if (path.size()>0)
        {
            //if an enemy is adjacent, attack them and set attacking to true.
            for (actor* _a : actors){
                if (coordinate(_a->col(),_a->row())==coordinate(path[path.size()-1].x,path[path.size()-1].y)){
                    attacking=true;
                }
            }
            //if you aren't attacking anyone, move along your path.
            if (attacking==false){
                moveOnPath();
            }

        }
        //reset the counter to 0
        counter=0;

        sprite.setPosition(x*16,y*16);
    }
    return;
}

void monster::moveOnPath()
{
    if (path.size()!=0){
        pos(path[path.size()-1].y,path[path.size()-1].x);
        path.erase(path.begin()+path.size()-1);
    }
}
