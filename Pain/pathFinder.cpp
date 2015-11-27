#include "pathFinder.h"
#include <queue>

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
    gCost=g;
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

struct comparator {
    bool operator() (const node item, const node n) const
    {
        int itemFcost=item.gCost+item.hCost;
        int nFcost=n.gCost+n.hCost;
        return nFcost<=itemFcost;
    }
};

std::vector<coordinate> pathFinder(std::vector<std::vector<bool> > _map, coordinate start, coordinate goal){

    WINDOW* win=initscr();
    curs_set(0);
    resize_term(100,50);
    wrefresh(win);
    noecho();
    cbreak();

    std::priority_queue<node, std::vector<node>, comparator> openSet;

    int distanceInNeighborset=1;

    std::vector<node> closedSet;
    std::vector<node> tempNeighborStorage;
    node currentNode(99999999,0);
    currentNode.gCost=0;

    openSet.push(currentNode);

    while (true){

            //==========CURSES DISPLAY======================
        for (int y=0;y<20;y++)
        {
            for (int x=0;x<20;x++)
            {
                if (_map[y][x]==1)
                {
                    mvwaddch(win,y,x,'#');
                }
                else
                {
                    mvwaddch(win,y,x,' ');
                }
            }
        }
        for (node _n:closedSet)
        {
            mvwaddch(win,_n.position.y,_n.position.x,'C');
        }
        refresh();
        //==============================================
        if (abs(currentNode.position.x-goal.x)==1 and abs(currentNode.position.y-goal.y)==1){
            std::cout << "Here";
            std::vector<coordinate> path;
            while(currentNode.position==start){
                path.push_back(currentNode.position);
                for (node _n : closedSet){
                    if (currentNode.parent==_n.position){
                        currentNode=_n;
                        std::cout << currentNode.position.x << "," << currentNode.position.y << std::endl;
                    }
                }
            }
            return path;
        }

        closedSet.push_back(currentNode);
        for (int y=-1; y<2; y++){
            for (int x=-1; x<2; x++){
                if (y==0 and x==0){
                    continue;
                }
                if (currentNode.position.x+x>=0 and currentNode.position.x+x<_map[0].size() and currentNode.position.y+y>=0 and currentNode.position.y+y<_map.size()){
                    if (_map[currentNode.position.y+y][currentNode.position.x+x]==0){
                        tempNeighborStorage.push_back(node(coordinate(currentNode.position.x+x,currentNode.position.y+y), goal, (currentNode.gCost+10+(4*abs(y)-abs(x)+1))));
                    }
                }
            }
        }

        for (node _n : tempNeighborStorage){
            int placeInSet=distanceInNeighborset;

            if (!vectorContains(_n.position, closedSet)){
                int newCostToMove = currentNode.gCost+manhattanDistance(currentNode.position,_n.position);

                if (newCostToMove>=_n.gCost){
                    _n.parent=currentNode.position;
                    _n.gCost=newCostToMove;
                }

                openSet.push(_n);
            }

        }
        tempNeighborStorage.clear();
        currentNode.gCost=openSet.top().gCost;
        currentNode.hCost=openSet.top().hCost;
        currentNode.parent=openSet.top().parent;
        currentNode.position.x=openSet.top().position.x;
        currentNode.position.y=openSet.top().position.y;

        openSet.pop();
    }
    std::cout << currentNode.position.x << "," << currentNode.position.y << std::endl;
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
    int distX = abs(currentNode.x-goal.x);
    int distY = abs(currentNode.y-goal.y);


    if (distX > distY)
    {
        return 14*distY + 10*(distX-distY);
    }
    return 14*distX + 10*(distY-distX);
}
