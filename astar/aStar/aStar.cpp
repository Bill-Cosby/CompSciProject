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
    gCost=costSoFar;
    hCost=getDistance(current,goal);
    position=current;
}

std::vector<coordinate> pathFinder(bool test_map[20][20], coordinate start, coordinate goal)
{
    WINDOW* win=initscr();
    curs_set(0);
    resize_term(100,50);
    wrefresh(win);
    noecho();
    cbreak();

    node currentNode;
    node neighbor;
    node temp;

    int lowestFIndex=0;

    std::vector<node> openNodes;    //set to be evaluated
    std::vector<BST<node> > nodeLibrary;
    std::vector<node> closedNodes;  //set already evaluated
    std::vector<coordinate> foundPath;
    std::vector<node> neighbors;

    nodeLibrary.push_back(BST<node>(node(start,goal,0)));
    BST<node>baseNode=nodeLibrary[0];
    baseNode.value.DDS=0;
    baseNode.value.gCost=-1;

    openNodes.push_back(node(coordinate(0,0),coordinate(0,0),0)); //initialize open set
    currentNode=baseNode.value;
    while (true)
    {
        nodeLibrary.erase(nodeLibrary.begin()+lowestFIndex);
        closedNodes.push_back(currentNode);
        //=============SET CURRENT NODE=================
//        for (node _n:openNodes)
//        {
//            if (_n.fCost()<currentNode.fCost() or _n.hCost<currentNode.hCost and _n.fCost()==currentNode.fCost())
//            {
//                currentNode=_n;
//            }
//        }
        //==============================================

        //==========CURSES DISPLAY======================
        for (int y=0;y<20;y++)
        {
            for (int x=0;x<20;x++)
            {
                if (test_map[y][x]==1)
                {
                    mvwaddch(win,y,x,'#');
                }
                else
                {
                    mvwaddch(win,y,x,' ');
                }
            }
        }
        for (node _n:openNodes)
        {

            mvwaddch(win,_n.position.y,_n.position.x, 'O');
        }
        for (node _n:closedNodes)
        {
            mvwaddch(win,_n.position.y,_n.position.x,'C');
        }
        refresh();
        //==============================================

        //=========PLACE CURRENT IN CLOSED==============
//        for (int i=0;i<openNodes.size();i++)
//        {
//            if (openNodes[i].position.x==currentNode.position.x&&openNodes[i].position.y==currentNode.position.y)
//            {
//                closedNodes.push_back(currentNode);
//                openNodes.erase(openNodes.begin()+i);
//            }
//        }
        //==============================================

        //===========IF FOUND GOAL======================
        if (currentNode.position.x == goal.x and currentNode.position.y == goal.y)
        {
            closedNodes.push_back(currentNode);
            coordinate tempStorage;
            tempStorage=currentNode.position;
            while (true)
            {
                for (int i=0;i<closedNodes.size();i++)
                {
                    if (closedNodes[i].position.x==tempStorage.x && closedNodes[i].position.y==tempStorage.y)
                    {
                        foundPath.push_back(tempStorage);
                        tempStorage=coordinate(closedNodes[i].parent.x, closedNodes[i].parent.y);
                        break;
                    }
                }
                if (tempStorage.x==start.x and tempStorage.y==start.y)
                {
                    return foundPath;
                }
            }
        }
        //==============================================

        //===============COMMENCE ASTAR=================

//              for each node in neighbor
        for (node _n : getNeighbors(currentNode,test_map,goal,currentNode.gCost))
        {
//              if neighbor is in closed list
            if (!nodeVectorContains(closedNodes,_n))
            {
//              set movement new Gcost
                int newMovementCostToNeighbor=currentNode.gCost+getDistance(currentNode.position,_n.position);
                if (!nodeLibraryContains(nodeLibrary,_n))
                {
                    if (newMovementCostToNeighbor < _n.gCost)
                    {
                        _n.gCost = newMovementCostToNeighbor;
                    }
                    _n.parent= currentNode.position;
                    nodeLibrary.push_back(BST<node>(_n));
                    nodeLibrary[nodeLibrary.size()-1].value.DDS=nodeLibrary.size()-1;
                    int placement = baseNode.add(nodeLibrary[nodeLibrary.size()-1].value);
                    nodeLibrary[placement].setNode(&nodeLibrary[nodeLibrary.size()-1]);
                    std::cout << nodeLibrary[placement].value.DDS;
                }
            }
        }
        lowestFIndex=baseNode.give();
        currentNode = nodeLibrary[lowestFIndex].value;
        //==============================================
    }
}

std::vector<node> getNeighbors(node Node, bool test_map[20][20], coordinate goal, int costSoFar)
{
    std::vector<node> neighbors;
    for (int x=-1;x<=1;x++){
    for (int y=-1;y<=1;y++){

            if (x==0 and y==0){
                continue;
            }

            int checkX=Node.position.x+x, checkY=Node.position.y+y;

            if (checkX>=0 and checkX<20 and checkY>=0 and checkY<20 and test_map[Node.position.y+y][Node.position.x+x]==0)
            {
                neighbors.push_back(node(coordinate(checkX,checkY), goal, costSoFar+getDistance(Node.position,coordinate(Node.position.x+x,Node.position.y+y))));
                neighbors[0].parent=Node.position;
            }
        }
    }

    return neighbors;
}

bool nodeVectorContains(std::vector<node> checkVector, node nodeChecking)
{
    for (node _n:checkVector)
    {
        if (_n.position.x==nodeChecking.position.x and _n.position.y==nodeChecking.position.y)
        {
            return true;
        }
    }
    return false;
}

bool nodeLibraryContains(std::vector<BST<node> > nodeLibrary, node nodeChecking)
{
    for (BST<node> _n:nodeLibrary)
    {
        if (_n.value.position.x==nodeChecking.position.x and _n.value.position.y==nodeChecking.position.y)
        {
            return true;
        }
    }
    return false;
}

int getDistance(coordinate nodeA, coordinate nodeB)
{
    int distX= abs(nodeA.x - nodeB.x);
    int distY= abs(nodeA.y - nodeB.y);

    if (distX > distY){
        return 14*distY + 10*(distX-distY);
    }
    else{
        return 14*distX + 10*(distY-distX);
    }

}
