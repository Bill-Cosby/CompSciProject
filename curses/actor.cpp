#include "actor.h"

actor::actor()
{
    player=true;
    _symbol='@';
}

actor::actor(int throwaway)
{
    player=false;
    _symbol='D';
}

void actor::aiMovement(std::vector<std::vector<tile> > test_map, coordinate goal, std::vector<actor> actors)
{
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
    if ((abs(x-goal.x)+abs(y-goal.y))>15 or musttouch==true)
    {
        musttouch=true;
        if (memory!=goal){
            memory=goal;
            path = pathFinder(test_map,coordinate(col(),row()),goal,noGo);
        }
    }
    if (path.size()>0)
    {
        pos(path[path.size()-1].y,path[path.size()-1].x);
        path.erase(path.begin()+path.size()-1);
    }
    return;
}

void actor::movement(std::vector<std::vector<tile> > map_, char ch)
{

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
    refresh();
}
