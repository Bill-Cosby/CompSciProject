#include "actor.h"
#include <cstdlib>

    char numpadControls[14] = {'8','5','2','4','6','7','9','3','1','c','o','i',27,'@'};
    char keyBrdControls[14] = {'w','.','s','d','a',-1,-1,-1,-1,'c','o','i',27,'@'};
    char VIKEYSControls[14] = {'h','.','j','k','l','y','u','m','n','c','o','i',27,'@'};
    coordinate directions[9] = {coordinate(0,-1),coordinate(0,0),coordinate(0,1),coordinate(1,0),coordinate(-1,0),coordinate(-1,-1),coordinate(1,-1),coordinate(1,1),coordinate(-1,1)};

player::player()
{
    _symbol='@';
    sprinting=false;
    controlled=true;
    health=100;
    attack=10;
    defense=0;
    speed=4;
    counter=4;
    sprinting=false;
}

monster::monster(int _speed, char symbol)
{
    counter=0;
    health=100;
    attack=10;
    defense=0;
    speed=_speed;
    _symbol=symbol;
    controlled=false;
    sprinting=false;
    memory=coordinate(-1,-1);
    path.resize(0);
}

bool monster::canSee(std::vector<std::vector<tile*> > test_map, coordinate checkSpot)
{
    int x1=col();
    int y1=row();
    int delta_x(checkSpot.x - x1);
    // if col() == checkSpot.x, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(checkSpot.y - y1);
    // if row() == checkSpot.y, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != checkSpot.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            if (test_map[y1][x1]->movementCost==-1){
                return false;
            }
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != checkSpot.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;
            if (test_map[y1][x1]->movementCost==-1){
                return false;
            }
        }
    }
    return true;
}

void monster::aiMovement(std::vector<std::vector<tile*> > test_map, std::vector<actor*> actors)
{
    coordinate goal;
    counter++;
    bool fuckDebugging=false;
    std::vector<coordinate> noGo;
    for (actor* _a : actors){
        noGo.push_back(coordinate(_a->col(),_a->row()));
        if (_a->controlled==true and canSee(test_map,coordinate(_a->col(),_a->row()))){
            goal = coordinate(_a->col(),_a->row());
        }
    }


    if (abs(goal.x-x)+abs(goal.y-y)<=2)
    {
        path.clear();
        fuckDebugging=true;
    }

    if (fuckDebugging==true){
        fuckDebugging=false;
    }

    if (canSee(test_map,goal))
    {
        memory=goal;
        path = pathFinder(test_map,coordinate(col(),row()),goal,noGo);
    }

    if (path.size()== 0)
    {
        if (memory.x!=-1 and memory.y!=-1)
        {
            path=pathFinder(test_map,coordinate(col(),row()),memory,noGo);
            memory=coordinate(-1,-1);
        }
        else if (coordinate(x,y) != post){
            path=pathFinder(test_map,coordinate(col(),row()),post,noGo);
        }
    }
    if (counter==5)
    {
        if (path.size()>0)
        {
            pos(path[path.size()-1].y,path[path.size()-1].x);
            path.erase(path.begin()+path.size()-1);
        }
        counter=0;
    }
    return;
}

void monster::moveOnPath(std::vector<std::vector<tile*> >_map)
{
    if (path.size()!=0){
        coordinate temp=coordinate(x,y);
        pos(path[path.size()-1].y,path[path.size()-1].x);
        for (coordinate _c : badPosition){
            if (canSee(_map,coordinate(_c)))
            {
                pos(temp.y,temp.x);
                memory=coordinate(-1,-1);
                noGo.push_back(coordinate(path[path.size()-1].x,path[path.size()-1].y));
                return;
            }
        }
        path.erase(path.begin()+path.size()-1);
    }
}

void player::movement(std::vector<std::vector<tile*> > *map_, char* ch, screen* scr)
{
    /*
    0 = NORTH
    1 = CENTER
    2 = SOUTH
    3 = EAST
    4 = WEST
    5 = NORTH-WEST
    6 = NORTH-EAST
    7 = SOUTH-EAST
    8 = SOUTH-WEST
    9 = CLOSE DOOR
    10 = OPEN DOOR
    11 = INVENTORY
    12 = PAUSE (options, quit game)
    13 = STATS
    */
    bool moveThroughDoor=true;
    std::vector<std::vector<tile*> > _map=*map_;


    for (int i=0;i<14;i++){

        if (*ch==numpadControls[i] or *ch==keyBrdControls[i] or *ch==VIKEYSControls[i]){

            if (i<9){


                if (_map[y+directions[i].y][x+directions[i].x]->movementCost!=-1){

                    if (_map[y+directions[i].y][x+directions[i].x]->isDoor==true){

                        moveThroughDoor=_map[y+directions[i].y][x+directions[i].x]->interactWithDoor(true);

                    }
                    if (moveThroughDoor==true){

                        pos(y+directions[i].y,x+directions[i].x);

                    }
                }
            }
            if (i==9 or i==10){
                bool opening=1-(-1*(i-10));
                char closeDirection=wgetch(scr->subwindow.sub);

                for (int i=0;i<9;i++){

                    if (i==1){
                        continue;
                    }
                    if (closeDirection==numpadControls[i] or closeDirection==keyBrdControls[i] or closeDirection==VIKEYSControls[i]){

                        _map[y+directions[i].y][x+directions[i].x]->interactWithDoor(opening);
                    }
                }
            }
        }
    }
//    if (*ch=='m'){
//        sprinting=!sprinting;
//        counter=0;
//        *ch=0;
//    }
//    if (getCounter()==getSpeed()){
//        if (*ch=='w' or *ch=='8'){
//            if (map_[y-1][x]->movementCost!=-1){
//                if (map_[y-1][x]->isDoor==true){
//                    moveThroughDoor=map_[y-1][x]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    y--;
//                }
//            }
//        }
//        if (*ch=='s' or *ch=='2'){
//            if (map_[y+1][x]->movementCost!=-1){
//                if (map_[y+1][x]->isDoor==true){
//                    moveThroughDoor=map_[y+1][x]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    y++;
//                }
//            }
//        }
//        if (*ch=='a' or *ch=='4'){
//            if (map_[y][x-1]->movementCost!=-1){
//                if (map_[y][x-1]->isDoor==true){
//                    moveThroughDoor=map_[y][x-1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x--;
//                }
//            }
//        }
//        if (*ch=='d' or *ch=='6'){
//            if (map_[y][x+1]->movementCost!=-1){
//                if (map_[y][x+1]->isDoor==true){
//                    moveThroughDoor=map_[y][x+1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x++;
//                }
//            }
//        }
//        if (*ch=='7')
//        {
//            if (map_[y-1][x-1]->movementCost!=-1){
//                if (map_[y-1][x-1]->isDoor==true){
//                    moveThroughDoor=map_[y-1][x-1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x--;
//                    y--;
//                }
//            }
//        }
//        if (*ch=='9')
//        {
//            if (map_[y-1][x+1]->movementCost!=-1){
//                if (map_[y-1][x+1]->isDoor==true){
//                    moveThroughDoor=map_[y-1][x+1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x++;
//                    y--;
//                }
//            }
//        }
//        if (*ch=='3')
//        {
//            if (map_[y+1][x+1]->movementCost!=-1){
//                if (map_[y+1][x+1]->isDoor==true){
//                    moveThroughDoor=map_[y+1][x+1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x++;
//                    y++;
//                }
//            }
//        }
//        if (*ch=='1')
//        {
//            if (map_[y+1][x-1]->movementCost!=-1){
//                if (map_[y+1][x-1]->isDoor==true){
//                    moveThroughDoor=map_[y+1][x-1]->openDoor();
//                }
//                if (moveThroughDoor==true){
//                    x--;
//                    y++;
//                }
//            }
//        }
//        if (*ch=='5')
//        {
//            y=y;
//            x=x;
//        }
//    }
}
