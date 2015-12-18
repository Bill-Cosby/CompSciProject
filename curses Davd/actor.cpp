#include "actor.h"
#include <cstdlib>

player::player()
{
    _symbol='@';
    controlled=true;
    speed=4;
    counter=0;
    sprinting=false;
}

monster::monster(int _speed, char symbol)
{
    counter=0;
    speed=_speed;
    _symbol=symbol;
    controlled=false;
    memory=coordinate(-1,-1);
    path.resize(0);
}

bool monster::canSee(std::vector<std::vector<tile> > test_map, coordinate checkSpot)
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
            if (test_map[y1][x1].movementCost==-1){
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
            if (test_map[y1][x1].movementCost==-1){
                return false;
            }
        }
    }
    return true;
}

void monster::aiMovement(std::vector<std::vector<tile> > test_map, coordinate goal, std::vector<actor> actors)
{
    counter++;
    std::vector<coordinate> noGo;
    for (actor _a : actors){
        noGo.push_back(coordinate(_a.col(),_a.row()));
    }

    if (goal == coordinate(x,y))
    {
        musttouch=false;
        path.clear();
        return;
    }


    if (canSee(test_map,goal))
    {
        memory=goal;
        path = pathFinder(test_map,coordinate(col(),row()),goal,noGo);
    }

    if (path.size()== 0)
    {
        if (memory.x!=-1 and memory.y!=-1)
        {
            path=pathFinder(test_map,coordinate(col(),row()),memory,noGo);
            memory=coordinate(-1,-1);
        }
        else if (coordinate(x,y) != post){
            path=pathFinder(test_map,coordinate(col(),row()),post,noGo);
        }
    }
    if (counter==5)
    {
        if (path.size()>0)
        {
            pos(path[path.size()-1].y,path[path.size()-1].x);
            path.erase(path.begin()+path.size()-1);
        }
        counter=0;
    }
    return;
}

void player::movement(std::vector<std::vector<tile> > map_, char ch)
{
    if (ch=='m'){
        sprinting=!sprinting;
        counter=0;
    }
    if (counter==speed-(speed/2*sprinting)){
        if (ch=='w' or ch=='8'){
            if (map_[y-1][x].movementCost!=-1){
                y--;
            }
        }
        if (ch=='s' or ch=='2'){
            if (map_[y+1][x].movementCost!=-1){
                y++;
            }
        }
        if (ch=='a' or ch=='4'){
            if (map_[y][x-1].movementCost!=-1){
                x--;
            }
        }
        if (ch=='d' or ch=='6'){
            if (map_[y][x+1].movementCost!=-1){
                x++;
            }
        }
        if (ch=='7')
        {
            if (map_[y-1][x-1].movementCost!=-1){
                x--;
                y--;
            }
        }
        if (ch=='9')
        {
            if (map_[y-1][x+1].movementCost!=-1){
                x++;
                y--;
            }
        }
        if (ch=='3')
        {
            if (map_[y+1][x+1].movementCost!=-1){
                x++;
                y++;
            }
        }
        if (ch=='1')
        {
            if (map_[y+1][x-1].movementCost!=-1){
                x--;
                y++;
            }
        }
        if (ch=='5')
        {
            y=y;
            x=x;
        }
    }
}
