#include "dungeon.h"

dungeon::dungeon()
{
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> mazeSize(0,1000);    //random number engine

    w=mazeSize(generator);
    h=mazeSize(generator);                              //self explanatory

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
    std::string mapOutput;
    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++)
        {
            if (dungeon_grid[i][j]==true)
            {
                mapOutput+='.';
            }
            else
            {
                mapOutput+='H';
            }
        }
        mapOutput+='\n';
    }

    std::ofstream myfile;
    myfile.open("map.txt");
    myfile << mapOutput;
    myfile.close();
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
            //std::cout << mazeTracker.top().x << "," << mazeTracker.top().y << std::endl;
            //std::cout << "limit:" << dungeon_grid[0].size() << ", " << dungeon_grid.size() << std::endl;
            while (direction==-1)
            {
                direction=mazeDirection(generator);
                if (mazeTracker.top().x+directions[direction-1*2].x>5 and mazeTracker.top().x+directions[direction-1*2].x<w-5 and mazeTracker.top().y+directions[direction-1*2].y>5 and mazeTracker.top().y+directions[direction-1*2].y<h-5)
                {
                    //std::cout << mazeTracker.top().x+directions[direction-1*2].x << "," << mazeTracker.top().y+directions[direction-1*2].y << std::endl;
                    //std::cout << "direction:" << direction << std::endl;
                    if (dungeon_grid[mazeTracker.top().y+directions[direction-1].y][mazeTracker.top().x+directions[direction-1].x]==false)
                    {
                        break;
                    }
                }
            }

            mazeTracker.push(coordinate(mazeTracker.top().x+directions[direction-1].x, mazeTracker.top().y+directions[direction-1].y));
            if (mazeTracker.top().x<w and mazeTracker.top().x<0 or mazeTracker.top().y>h or mazeTracker.top().y<0)
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

coordinate::coordinate(int x_t,int y_t)
{
    x=x_t;
    y=y_t;
}

coordinate::coordinate()
{
}
