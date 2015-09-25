#include "aStar.h"
#include <unordered_set>
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
    position=current;
}

std::vector<coordinate> pathFinder(bool test_map[20][20], coordinate start, coordinate goal)
{
    int costSoFar=0;
    int lowestF_Cost=99999999;

    node currentNode;
    node neighbor;
    node temp;

    std::vector<node> openNodes;    //set to be evaluated
    std::vector<node> closedNodes;  //set already evaluated
    std::vector<coordinate> foundPath;
    std::vector<node> neighbors;

    openNodes.push_back(node(start,goal,0)); //initialize open set
    while (openNodes.size()!=0)
    {
        //=============SET CURRENT NODE=================
        currentNode = openNodes[0];
        for (int i=0;i<openNodes.size();i++){
            if (openNodes[i].fCost()<currentNode.fCost() || openNodes[i].fCost()==currentNode.fCost() && openNodes[i].hCost<currentNode.hCost)
            {
                currentNode=openNodes[i];
            }
        }
        //==============================================

        //REMOVE NODE FROM openNodes AND ADD TO closedNodes
        for (int i=0;i<openNodes.size();i++)
        {
            if (openNodes[i].position.x==currentNode.position.x&&openNodes[i].position.y==currentNode.position.y)
            {
                openNodes.erase(openNodes.begin()+i);
                closedNodes.push_back(currentNode);
            }
        }

        if (currentNode.position.x == goal.x and currentNode.position.y == goal.y)
        {
            //things!!!
        }
        //==============================================


        neighbors=getNeighbors(currentNode,test_map,goal,costSoFar);
        for (int i=0;i<neighbors.size();i++)
        {
            neighbor=neighbors[i];
            for (int j=0;j<closedNodes.size();j++)
            {
                if (test_map[neighbors[i].position.x][neighbors[i].position.y]!=1 or closedNodes[j].position.x!=neighbors[i].position.x and closedNodes[j].position.y!=neighbors[i].position.y)
                {
                    int newGCost = currentNode.gCost + getDistance(currentNode, neighbors[i]);
                    if (openNodes.size()==0)
                    {
                        neighbors[i].gCost = newGCost;
                        neighbors[i].hCost = getDistance(neighbors[i], node(goal,goal,0));
                        neighbors[i].parent=currentNode.position;
                        openNodes.push_back(neighbors[i]);
                        std::cout << currentNode.position.x << " , " << currentNode.position.y << std::endl;
                    }

                    for (int k=0;k<openNodes.size();k++)
                    {
                        if (openNodes[k].position.x!=neighbors[i].position.x and openNodes[k].position.y!=neighbors[i].position.y)
                        {
                            if (newGCost<neighbors[i].gCost)
                            {
                                neighbors[i].gCost = newGCost;
                                neighbors[i].hCost = getDistance(neighbors[i], node(goal,goal,0));
                                neighbors[i].parent=currentNode.position;
                            }
                        }
                    }
                }
            }
        }


    }
}

float heuristic(coordinate current, coordinate goal)
{
    return abs(current.x-goal.x)+abs(current.y-current.y);
}

std::vector<node> getNeighbors(node Node, bool test_map[][20], coordinate goal, int costSoFar)
{
    std::vector<node> neighbors;
    for (int x=-1;x<=1;x++){
        for (int y=-1;y<=1;y++){
            if (x==0 and y==0){
                continue;
            }
            int checkX=Node.position.x+x, checkY=Node.position.y+y;
            if (checkX>=0 and checkX<20 and checkY>=0 and checkY<20)
            {
                neighbors.push_back(node(coordinate(checkX,checkY), goal, costSoFar));
            }
        }
    }

    return neighbors;
}

int getDistance(node nodeA, node nodeB)
{
    int distX= abs(nodeA.position.x - nodeB.position.x);
    int distY= abs(nodeA.position.y - nodeB.position.y);

    if (distX > distY){
        return 14*distY + 10*(distX-distY);
    }
    return 14*distY + 10*(distY-distX);
}
