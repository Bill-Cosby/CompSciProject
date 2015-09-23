#include "aStar.h"

coordinate::coordinate(int x_t, int y_t)
{
    x=x_t;
    y=y_t;
}

coordinate::coordinate()
{
    x=0;
    y=0;
}

node::node(coordinate current, coordinate goal, coordinate position_t, int costSoFar)
{
    g=costSoFar+10;
    h=heuristic(current, goal);
    f=g+h;
    position=position_t;
}

std::vector<coordinate> pathFinder(bool test_map[20][20], coordinate start, coordinate goal)
{
    int costSoFar=0;
    std::vector<node> openNodes;
    std::vector<node> closedNodes;
    while (true)
    {

    }
}

float heuristic(coordinate current, coordinate goal)
{
    return abs(current.x-goal.x)+abs(current.y-current.y);
}
