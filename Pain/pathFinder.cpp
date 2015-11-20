#include "pathFinder.h"

node::node(int h,int g)
{
    hCost=h;
    gCost=g;
    Left=NULL;
    Right=NULL;
}

node::node(coordinate pos, coordinate _goal, int g)
{
    position=pos;
    hCost=manhattanDistance(position, _goal);
    Left=NULL;
    Right=NULL;
}
node::node(int h, int g, node* L, node* R)
{
    hCost=h;
    gCost=g;
    Left=L;
    Right=R;
}

bool node::contains(node item)
{
    if (item<=*this)
    {
        if (item==*this)
        {
            return true;
        }
        if (Left){
           Left->contains(item);
        }
    }
    if (Right){
        Right->contains(item);
    }
    return false;
}

void node::add(node* item)
{
    if (*item<=*this){
        if (Left!=NULL){
            Left->add(item);
        }else{
            Left=item;
        }
        return;
    }
    if (Right!=NULL){
        Right->add(item);
    }else{
        Right=item;
    }
    return;
}

node node::give()
{
    if (Left->Left==NULL){
        node temp=*Left;
        if (Left->Right!=NULL){
            Left=Left->Right;
        }else{
            Left=NULL;
        }
        return temp;
    }
}

std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > _map, coordinate start, coordinate goal){
    int distanceInNeighborset=1;
    std::cout << _map[0].size() << std::endl;

    std::vector<node> closedSet;
    std::vector<node> neighborSet;

    node baseNode(std::numeric_limits<double>::infinity(),0);
    baseNode.position=coordinate(0,0);
    node currentNode=baseNode;
    neighborSet.push_back(currentNode);
    baseNode.add(&neighborSet[0]);

    while (baseNode.Left!=NULL){
        if (currentNode.position==goal){
            std::cout << "Here\n";
        }

        closedSet.push_back(currentNode);
        std::vector<node> tempNeighborStorage=currentNode.findNeighbors(_map,goal);
        std::cout << tempNeighborStorage.size();
        for (node _n : tempNeighborStorage){
            neighborSet.push_back(_n);
        }

        for (node _n : tempNeighborStorage){
            int placeInSet=distanceInNeighborset;
            if (vectorContains(_n.position, closedSet)){
                continue;
            }
            int newCostToMove = currentNode.gCost+manhattanDistance(currentNode.position,goal);

            if (newCostToMove>=_n.gCost){
                neighborSet[placeInSet].parent=currentNode.position;
                neighborSet[placeInSet].gCost=newCostToMove;
            }

            baseNode.add(&neighborSet[placeInSet]);

            placeInSet++;
        }
        currentNode=baseNode.give();


        distanceInNeighborset+=tempNeighborStorage.size();

    }

}

std::vector<node> node::findNeighbors(std::vector<std::vector<bool> > _map, coordinate goal)
{
    std::vector<node> neighbors;
    for (int y=-1; y<2; y++){
        for (int x=-1; x<2; x++){
            if (y==0 and x==0){
                continue;
            }
            std::cout << position.x+x << "," << position.y+y << std::endl;
            if (position.x+x>=0 and position.x+x<_map[0].size() and position.y+y>=0 and position.y+y<_map.size()){
                if (_map[position.y+y][position.x+x]==0){
                    neighbors.push_back(node(position, position, gCost + ( abs(x) + abs(y) -1 )));
                    std::cout << "Here\n";
                }

            }
        }
    }
    return neighbors;
}

bool vectorContains(coordinate currentPosition, std::vector<node> vectorChecker)
{
    for (node _n : vectorChecker){
        if (_n.position==currentPosition){
            return true;
        }
    }
    return false;
}

int manhattanDistance(coordinate currentNode, coordinate goal)
{
    return abs(goal.x-currentNode.x)+abs(goal.y-currentNode.y);
}
