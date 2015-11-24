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
    item->Left=NULL;
    item->Right=NULL;
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
    node temp=*Left;
    if (Left->Left==NULL){

        node temp=*Left;
        if (Left->Right!=NULL){

            Left=Left->Right;

        }else{

            Left=NULL;

        }
    }
    return temp;
}

std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > _map, coordinate start, coordinate goal){
    int distanceInNeighborset=1;
    std::cout << _map[0].size() << std::endl;

    std::vector<node> closedSet;
    std::vector<node> neighborSet;
    std::vector<node> tempNeighborStorage;

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
        for (int y=-1; y<2; y++){
            for (int x=-1; x<2; x++){
                if (y==0 and x==0){
                    continue;
                }
                if (currentNode.position.x+x>=0 and currentNode.position.x+x<_map[0].size() and currentNode.position.y+y>=0 and currentNode.position.y+y<_map.size()){
                    if (_map[currentNode.position.y+y][currentNode.position.x+x]==0){
                        std::cout << currentNode.position.x+x << "," << currentNode.position.y+y << std::endl;
                        tempNeighborStorage.push_back(node(coordinate(currentNode.position.x+x,currentNode.position.y+y), goal, currentNode.gCost + ( abs(x) + abs(y) -1 )));
                    }
                }
            }
        }
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



bool vectorContains(coordinate currentPosition, std::vector<node> vectorChecker)
{
    for (node _n : vectorChecker){
        node temp=_n;
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
