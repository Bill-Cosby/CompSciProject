#include "actor.h"

player::player()
{
    x=3;
    y=3;
    symbol='@';
}

void player::movement(std::vector<std::vector<tile> > map_, char ch)
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
}
