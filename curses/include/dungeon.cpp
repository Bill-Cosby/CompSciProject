#include "dungeon.h"

dungeon::dungeon()
{
    std::vector<std::vector<bool> > temp_grid;
    int firstY=-1,firstX;
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> mazeSize(0,1000);    //random number engine
    w=2000;
    h=2000;                              //self explanatory

    dungeon_grid.resize(h);
    for (int i=0;i<h;i++)                                   //initialize dungeon_grid to false
    {
        dungeon_grid[i].resize(w);
        for (int j=0;j<w;j++)
        {
            dungeon_grid[i][j]=false;
        }
    }
                                            //find maze beginning
    mazeBegin.x=w/2;
    mazeBegin.y=h/2;
    hallwayMaker();
    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++){
            if (dungeon_grid[i][j]==true and firstY==-1){
                firstY=i;
                firstX=j;
                temp_grid.resize(h-firstY);
            }
            if (dungeon_grid[i][j]== true and j<firstX){
                firstX=j;
            }
        }
    }
    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++)
        {
            if (dungeon_grid[i][j]==true)
            {
                dungeon_grid[i-firstY][j-firstX]=true;
                dungeon_grid[i][j]=false;
            }
        }
    }
    dungeon_grid.resize(h-firstY);
    for (int i=0;i<dungeon_grid.size();i++)
    {
        dungeon_grid[i].resize(w-firstX);
    }



}

int dungeon::Passable(int Mx, int My)
{
    if (Mx>=0 and Mx<w and My>=0 and My<h){
        if (dungeon_grid[My][Mx]==0){
            return 1;
        }
    }
    return 0;
}

void dungeon::hallwayMaker()
{
    std::default_random_engine generator(time(0));          //random number engine
    std::uniform_int_distribution<int> mazeDirection(1,4);
    int direction=-1;
    std::stack<coordinate> mazeTracker;                     //maze stack
    mazeTracker.push(mazeBegin);                            //initialize stack
    dungeon_grid[mazeTracker.top().y][mazeTracker.top().x]=true;


    for (int i=0;i<50000;i++)
    {
        if (mazeTracker.size()!=0)
        {
            while (direction==-1)
            {
                direction=mazeDirection(generator);
                if (mazeTracker.top().x+directions[direction-1*2].x>5 and mazeTracker.top().x+directions[direction-1*2].x<w-5 and mazeTracker.top().y+directions[direction-1*2].y>5 and mazeTracker.top().y+directions[direction-1*2].y<h-5)
                {
                    if (dungeon_grid[mazeTracker.top().y+directions[direction-1].y][mazeTracker.top().x+directions[direction-1].x]==false)
                    {
                        break;
                    }
                }
            }

            mazeTracker.push(coordinate(mazeTracker.top().x+directions[direction-1].x, mazeTracker.top().y+directions[direction-1].y));

            if (mazeTracker.top().x<w and mazeTracker.top().x<0 or mazeTracker.top().y>h or mazeTracker.top().y<0 and mazeTracker.size()>0)
            {
                mazeTracker.pop();
            }

            else
            {
                dungeon_grid[mazeTracker.top().y][mazeTracker.top().x]=true;
            }
            direction=-1;
        }

        else
        {
            break;
        }
    }
}
