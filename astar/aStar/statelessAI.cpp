#include "statelessAI.h"

firstAi::firstAi()
{
    position=coordinate(0,0);
    food = coordinate(15,8);
    shit = coordinate(2,2);
    hunger=0;
    pooper=10;
}

void firstAi::decide(bool test_map[20][20])
{
    hunger--;
    pooper--;
    if (position.x==food.x and position.y==food.y)
    {
        hunger=20;
    }
    if (position.x==shit.x and position.y==shit.y)
    {
        pooper=20;
    }
    if (aiPath.size()==0)
    {
        if (hunger<=0)
        {
            goal=food;
        }
        else if (pooper<=0)
        {
            goal=shit;
        }
        if (position.x!=goal.x and position.y!=goal.y)
        {
            aiPath=pathFinder(test_map,position,goal);
        }
    }
    else if(goal.x==position.x and goal.y==position.y)
    {
        aiPath.clear();
    }
    if (aiPath.size()!=0)
    {
        placeInPath=aiPath.size()-1;
        position=aiPath[placeInPath];
        aiPath.erase(aiPath.begin()+placeInPath);
    }
}
