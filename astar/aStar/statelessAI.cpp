#include "statelessAI.h"

firstAi::firstAi()
{
    position=coordinate(0,0);
}

void firstAi::decide(bool test_map[20][20])
{
    if (aiPath.size()==0)
    {
        while (true)
        {
            int goal_x,goal_y;
            std::cout << "Where am I walking?: ";
            std::cin >> goal_x;
            std::cout << ",";
            std::cin >> goal_y;
            if (test_map[goal_y][goal_x]==1)
            {
                std::cout << "That's a wall man\n";
            }
            else
            {
                goal=coordinate(goal_x,goal_y);
                break;
            }
        }
    }
    else
    {
        position=aiPath[0];
    }
    aiPath=pathFinder(test_map,position,goal);
}
