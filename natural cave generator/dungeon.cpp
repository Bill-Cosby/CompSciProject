#include "dungeon.h"

dungeons::dungeons()
{
    std::default_random_engine generator(time(0));
    std::ofstream myfile;
    std::uniform_int_distribution<int> mazeSize(500,1000);
    std::uniform_int_distribution<int> mazestart(0,1000);
//    w=mazeSize(generator);
//    h=w;
    w=5;
    h=5;
    mazebegin.x=2;
    mazebegin.y=3;
    directions[0]=coordinate(0,-1);
    directions[1]=coordinate(1,0);
    directions[2]=coordinate(0,1);
    directions[3]=coordinate(-1,0);
//    while(true)
//    {
//        mazebegin.x=mazestart(generator);
//        mazebegin.y=mazestart(generator);
//        if (mazebegin.x<w and mazebegin.y<h)
//        {
//            break;
//        }
//    }

    dungeon_grid.resize(h);

    for (int i=0;i<h;i++)
    {
        dungeon_grid[i].resize(w);
        for (int j=0;j<w;j++)
        {
            dungeon_grid[i][j]=false;
        }
    }

    std::string dungeonTextFile;
    hallwaymaker();
    for (int i=0;i<dungeon_grid.size();i++)
    {
        for (int j=0;j<dungeon_grid.size();j++)
        {
            if (dungeon_grid[i][j]==true)
            {
                dungeonTextFile+='.';
            }
            else
            {
                dungeonTextFile+='H';
            }
        }
        dungeonTextFile+='\n';
    }
    myfile.open ("map.txt");
    myfile << dungeonTextFile;
    myfile.close();
}

void dungeons::hallwaymaker()
{
    //Random Number Generators
    std::default_random_engine generator(time(0));
    std::stack<coordinate> mazetracker;
    std::vector<int>directionsToCheck;
    std::uniform_int_distribution<int> roomDirection(1,4);

    //variable declaration
    int direction;
    int temp;
    bool timeToBreak;

    //begin stack
    mazetracker.push(mazebegin);
    dungeon_grid[mazetracker.top().y][mazetracker.top().x]=true;
    //algorithm begin
    while (true)
    {
        if (mazetracker.size()==0)
        {
            //std::cout << "Stack is empty\n";
            break;
        }
        directionsToCheck=adjacencyCheck(mazetracker.top(), dungeon_grid);
        //std::cout << mazetracker.top().x << "," << mazetracker.top().y << "\t" << direction << std::endl;
        if (directionsToCheck.size()==0)
        {
            //std::cout << "No where else to go\n";
            break;
        }
        while (timeToBreak==false)
        {
            temp=roomDirection(generator);
            for (int i=0;i<directionsToCheck.size();i++)
            {
                std::cout << directionsToCheck[i] << std::endl;
                if (directionsToCheck[i]==temp)
                {
                    direction=temp;
                    std::cout << direction << std::endl;
                    timeToBreak=true;
                }
            }
            std::cout << std::endl;
        }
        timeToBreak=false;
        if (dungeon_grid[mazetracker.top().y+directions[direction-1].y][mazetracker.top().x+directions[direction-1].x]==false and mazetracker.top().y+directions[(direction-1)*2].y>0 and mazetracker.top().y+directions[direction-1*2].y<h and mazetracker.top().y+directions[(direction-1)*2].y>0 and mazetracker.top().x+directions[(direction-1)*2].x<w)
        {
            mazetracker.push(coordinate(mazetracker.top().x+directions[direction-1].x,mazetracker.top().y+directions[direction-1].y));
            dungeon_grid[mazetracker.top().y][mazetracker.top().x]=true;
//            mazetracker.push(coordinate(mazetracker.top().x+directions[direction-1].x,mazetracker.top().y+directions[direction-1].y));
//            dungeon_grid[mazetracker.top().y][mazetracker.top().x]=true;
        }
        else
        {
            mazetracker.pop();
            std::cout << "pop!\n";
        }
         std::cout << mazetracker.top().x << "," << mazetracker.top().y << std::endl;
        for (int i=0;i<5;i++)
        {
            for (int j=0;j<5;j++)
            {
                if (mazetracker.top().x==j and mazetracker.top().y == i)
                {
                    std::cout<< "!";
                }
                else
                {
                    std::cout << dungeon_grid[i][j];
                }
            }
            std::cout << std::endl;
        }
        directionsToCheck.clear();
    }
}




std::vector<int> adjacencyCheck(coordinate spotToCheck, std::vector<std::vector<bool> > dungeon_grid)
{
    std::vector<int> directionsPossible;
    if (spotToCheck.y-1>=0 and dungeon_grid[spotToCheck.y-1][spotToCheck.x]==false)
    {
        directionsPossible.push_back(1);
    }
    if (spotToCheck.x+1<=dungeon_grid[0].size() and dungeon_grid[spotToCheck.y][spotToCheck.x+1]==false)
    {
        directionsPossible.push_back(2);
    }
    if (spotToCheck.y+1<=dungeon_grid.size() and dungeon_grid[spotToCheck.y+1][spotToCheck.x]==false)
    {
        directionsPossible.push_back(3);
    }
    if (spotToCheck.x-1>=0 and dungeon_grid[spotToCheck.y][spotToCheck.x-1]==false)
    {
        directionsPossible.push_back(4);
    }
    return directionsPossible;
}
room::room(int w_t,int h_t, int x_l, int y_l)
{
    w=w_t;
    h=h_t;
    x=x_l;
    y=y_l;
}

coordinate::coordinate(int x_t, int y_t)
{
    x=x_t;
    y=y_t;
}
coordinate::coordinate()
{

}
