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

node::node()
{
}

node::node(coordinate current, coordinate goal, int costSoFar)
{
    gCost=10+costSoFar;
    hCost=heuristic(current, goal);
    fCost=gCost+hCost;
    position=current;
}

std::vector<coordinate> pathFinder(bool test_map[20][20], coordinate start, coordinate goal)
{
    int costSoFar=0;
    int lowestF_Cost=99999999;

    node currentNode;


    std::vector<node> openNodes;    //set to be evaluated
    std::vector<node> closedNodes;  //set already evaluated
    std::vector<coordinate> foundPath;


    openNodes.push_back(node(start,goal,0)); //initialize open set

    while (true)
    {
        //=============SET CURRENT NODE=================
        for (int i=0;i<openNodes.size();i++)
        {
            if (openNodes[i].fCost<lowestF_Cost)
            {
                lowestF_Cost=openNodes[i].fCost;
                currentNode=openNodes[i];
            }
        }

        //==============================================

        //====ADD NODE TO CLOSED AND REMOVE FROM OPEN===
        for (int i=0;i<openNodes.size();i++)
        {
            if (openNodes[i].position.x==currentNode.position.x and openNodes[i].position.y==currentNode.position.y)
            {
                closedNodes.push_back(openNodes[i]);
                openNodes.erase(openNodes.begin()+i);
            }
            if (currentNode.position.x==goal.x&&currentNode.position.y==goal.y)
            {
                while (currentNode.parent.x!=start.x and currentNode.parent.y!=start.y)
                {
                    foundPath.push_back(currentNode.parent);
                    for (int j=0;j<closedNodes.size();i++)
                    {
                        if (closedNodes[j].position.x==currentNode.parent.x&&closedNodes[j].position.y==currentNode.parent.y)
                        {
                            currentNode=closedNodes[j];
                            break;
                        }
                    }
                }
                return foundPath;
            }
        }
        //==============================================

        //=======FOR EACH NEIGHBOR IN CURRENT NODE======
        for (int x=-1;x<2;x++)
        {
            for (int y=-1;y<2;y++)
            {
                //====if neighbor is current node====
                if (x!=0&&y!=0)
                {
                    node neighbor=node(coordinate(currentNode.position.x+x,currentNode.position.y+y),goal, currentNode.gCost);
                    //====if neighbor is walkable====
                    if (test_map[neighbor.position.x][neighbor.position.y]==0)
                    {
                        for (int i=0;i<closedNodes.size();i++)
                        {
                            //====if neighbor isn't a closed node====
                            if (neighbor.position.x!=closedNodes[i].position.x && neighbor.position.y!=closedNodes[i].position.y)
                            {
                                for (int i=0;i<openNodes.size();i++)
                                {
                                    int newGCost=currentNode.gCost+14;
                                    if (openNodes[i].position.x!=neighbor.position.x && openNodes[i].position.y!=neighbor.position.y || newGCost<neighbor.gCost)
                                    {
                                        neighbor.parent=currentNode.position;
                                        if (newGCost<neighbor.gCost)
                                        {
                                            openNodes.push_back(neighbor);
                                        }
                                    }
                                }
                            }
                            if (openNodes.size()==0)
                            {
                                openNodes.push_back(neighbor);
                            }
                        }
                    }
                }
            }
        }
        //===============================================
    }
}

float heuristic(coordinate current, coordinate goal)
{
    return abs(current.x-goal.x)+abs(current.y-current.y);
}
