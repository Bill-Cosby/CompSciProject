#include "dungeon.h"

dungeons::dungeons()
{
    std::mt19937 generator(time(0));
    std::uniform_int_distribution<int> distributor(5,30);
    std::uniform_int_distribution<int> roomsize(2,40);
    std::uniform_int_distribution<int> location(30,1000);
    w=location(generator);
    h=location(generator);
    dungeon_grid.resize(h);
    for (int i=0;i<dungeon_grid.size();i++)
    {
        dungeon_grid[i].resize(w);
    }
//    int numberOfRooms=distributor(generator);
//    for (int i=0;i<numberOfRooms;i++)
//    {
//        rooms.push_back(room(roomsize(generator),roomsize(generator),location(generator),location(generator)));
//        for (int j=rooms[i].y;j<rooms[i].h+rooms[i].y;j++)
//        {
//            for (int k=rooms[i].x;k<rooms[i].w+rooms[i].x;k++)
//            {
//                if (k<dungeon_grid[0].size() and k>0 and j<dungeon_grid.size() and j>0)
//                {
//                    //dungeon_grid[j][k]=true;
//                }
//            }
//        }
//    }
    while (true)
    {
        mazebegin.x=location(generator);
        mazebegin.y=location(generator);
        if (mazebegin.x<=dungeon_grid[0].size() and mazebegin.y<=dungeon_grid.size() and dungeon_grid[mazebegin.x][mazebegin.y]==false)
        {
            break;
        }
    }
    hallwaymaker();
    std::string mapoutput;
    for (int i=0;i<dungeon_grid.size();i++)
    {
        for (int j=0;j<dungeon_grid[0].size();j++)
        {
            if (dungeon_grid[i][j]==true)
            {
                mapoutput+='.';
            }
            else
            {
                mapoutput+='O';
            }
        }
        mapoutput+='\n';
    }
    std::ofstream myfile;
    myfile.open("map.txt");
    myfile << mapoutput;
    myfile.close();
}

void dungeons::hallwaymaker()
{
    int test=-1;
    std::mt19937 generator(time(0));
    std::uniform_int_distribution<int> diceroller(1,4);
    int direction=0, previousMove;
    std::stack<coordinate> mazeEnd;
    mazeEnd.push(mazebegin);
    dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
    while(true)
    {
        test++;
        previousMove=direction;
        direction=diceroller(generator);
        std::cout << mazeEnd.top().x << "," << mazeEnd.top().y << "\tdirection: " << direction << std::endl;
        if (mazeEnd.top().y-2>0 and dungeon_grid[mazeEnd.top().x][mazeEnd.top().y-2]==false and direction==1)
        {
            mazeEnd.push(coordinate(mazeEnd.top().x,mazeEnd.top().y-1));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
            mazeEnd.push(coordinate(mazeEnd.top().x,mazeEnd.top().y-1));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
        }
        else if (mazeEnd.top().x+2<dungeon_grid[0].size()-1 and dungeon_grid[mazeEnd.top().x+2][mazeEnd.top().y]==false and direction==2)
        {
            mazeEnd.push(coordinate(mazeEnd.top().x+1,mazeEnd.top().y));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
            mazeEnd.push(coordinate(mazeEnd.top().x+1,mazeEnd.top().y));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
        }
        else if (mazeEnd.top().y+2<dungeon_grid.size() and dungeon_grid[mazeEnd.top().x][mazeEnd.top().y+2]==false and direction==3)
        {
            mazeEnd.push(coordinate(mazeEnd.top().x,mazeEnd.top().y+1));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
            mazeEnd.push(coordinate(mazeEnd.top().x,mazeEnd.top().y+1));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
        }
        else if (mazeEnd.top().x-2>0 and dungeon_grid[mazeEnd.top().x-2][mazeEnd.top().y]==false and direction==4)
        {
            mazeEnd.push(coordinate(mazeEnd.top().x-1,mazeEnd.top().y));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
            mazeEnd.push(coordinate(mazeEnd.top().x-1,mazeEnd.top().y));
            dungeon_grid[mazeEnd.top().x][mazeEnd.top().y]=true;
        }
        else
        {
            mazeEnd.pop();
        }
        if (mazeEnd.top().x==mazebegin.x and mazeEnd.top().y==mazebegin.y or test==60000)
        {
            std::cout << test;
            break;
        }
    }
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
