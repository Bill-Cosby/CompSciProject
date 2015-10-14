#include "actor.h"


void actor::movement(std::vector<std::vector<tile> > map_, char ch)
{

    if (ch=='w' or ch=='8'){
        if (map_[_row-1][_col].movementCost!=-1){
            _row--;
        }
    }
    if (ch=='s' or ch=='2'){
        if (map_[_row+1][_col].movementCost!=-1){
            _row++;
        }
    }
    if (ch=='a' or ch=='4'){
        if (map_[_row][_col-1].movementCost!=-1){
            _col--;
        }
    }
    if (ch=='d' or ch=='6'){
        if (map_[_row][_col+1].movementCost!=-1){
            _col++;
        }
    }
    if (ch=='7')
    {
        if (map_[_row-1][_col-1].movementCost!=-1){
            _col--;
            _row--;
        }
    }
    if (ch=='9')
    {
        if (map_[_row-1][_col+1].movementCost!=-1){
            _col++;
            _row--;
        }
    }
    if (ch=='3')
    {
        if (map_[_row+1][_col+1].movementCost!=-1){
            _col++;
            _row++;
        }
    }
    if (ch=='1')
    {
        if (map_[_row+1][_col-1].movementCost!=-1){
            _col--;
            _row++;
        }
    }
}
