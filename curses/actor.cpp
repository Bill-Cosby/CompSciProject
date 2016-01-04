#include "actor.h"
#include <cstdlib>

    char numpadControls[16] = {'8','5','2','6','4','7','9','3','1','c','o','i',27,'@','e','5'};
    char keyBrdControls[16] = {'w','.','s','d','a',-1,-1,-1,-1,'c','o','i',27,'@','e',10};
    char VIKEYSControls[16] = {'h','.','j','k','l','y','u','m','n','c','o','i',27,'@','e',10};
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

void player::movement(std::vector<std::vector<tile*> > *map_,std::vector<item*> *localItems, char* ch, screen* scr)
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
    12 = PAUSE(options, quit game)/EXIT MENU
    13 = STATS
    14 = EXAMINE
    15 = EXECUTE
    */
    bool moveThroughDoor=true;
    char inventoryMovement;
    char closeDirection;
    char examineDirection;
    std::vector<std::vector<tile*> > _map=*map_;


    for (int i=0;i<16;i++){

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
                closeDirection=wgetch(scr->subwindow.sub);

                for (int i=0;i<9;i++){

                    if (i==1){
                        continue;
                    }
                    if (closeDirection==numpadControls[i] or closeDirection==keyBrdControls[i] or closeDirection==VIKEYSControls[i]){

                        _map[y+directions[i].y][x+directions[i].x]->interactWithDoor(opening);
                    }
                }
            }
            if (i == 14){
                examineDirection = wgetch(scr->subwindow.sub);
                for (int i=0;i<9;i++){
                    if (examineDirection==numpadControls[i] or examineDirection==keyBrdControls[i] or examineDirection==VIKEYSControls[i]){
                        examineGround(scr, localItems, coordinate(directions[i].x+x,directions[i].y+y));
                        return;
                    }
                }

            }
            if (i == 11){
                openInventory(scr);
            }
        }
    }
}

void player::openInventory(screen* scr)
{
    bool activeWindow=0; //0 means inventory, not equipment
    int itemSelected=0;
    char ch=-1;
    while (true){

        wborder(scr->subwindow.inventoryWindow,0,0,0,0,0,0,0,0);
        wborder(scr->subwindow.equipmentWindow,0,0,0,0,0,0,0,0);
        if (activeWindow==0){
            wattron(scr->subwindow.inventoryWindow,A_BLINK);
        }
        else{
            wattron(scr->subwindow.equipmentWindow,A_BLINK);
        }

        mvwaddstr(scr->subwindow.inventoryWindow,0,3,"inventory");
        mvwaddstr(scr->subwindow.equipmentWindow,0,3,"equipment");

        wattroff(scr->subwindow.inventoryWindow,A_BLINK);
        wattroff(scr->subwindow.equipmentWindow,A_BLINK);

        for (int i=0;i<inventory.size();i++){
            if (itemSelected==i and activeWindow==0){
                wattron(scr->subwindow.inventoryWindow,A_REVERSE);
            }
            mvwaddstr(scr->subwindow.inventoryWindow,i+1,2,inventory[i]->name.c_str());
            wattroff(scr->subwindow.inventoryWindow,A_REVERSE);
        }

        for (int i=0;i<equipment.size();i++){
            if (itemSelected==i and activeWindow==1){
                wattron(scr->subwindow.equipmentWindow,A_REVERSE);
            }
            mvwaddstr(scr->subwindow.equipmentWindow,i+1,2,equipment[i]->name.c_str());
            wattroff(scr->subwindow.equipmentWindow,A_REVERSE);
        }

        wrefresh(scr->subwindow.equipmentWindow);
        wrefresh(scr->subwindow.inventoryWindow);
        if (activeWindow==0){
            ch=wgetch(scr->subwindow.inventoryWindow);
        }
        else{
            ch=wgetch(scr->subwindow.equipmentWindow);
        }
        for (int i=0;i<16;i++){
            if (ch==numpadControls[i] or ch==keyBrdControls[i] or ch==VIKEYSControls[i]){
                if (i==0){
                    if (itemSelected-1>=0){
                        itemSelected--;
                    }
                }
                if (i==2){
                    if (activeWindow==0){
                        if (itemSelected+1<=inventory.size()){
                            itemSelected++;
                        }
                    }
                    else{
                        if (itemSelected+1<=equipment.size()){
                            itemSelected++;
                        }
                    }
                }
                if (i==3 or i==4){
                    activeWindow= 1-activeWindow;
                }

                if (i==15){
                    if (activeWindow==0){
                        inventory[itemSelected]->selected=true;
                    }
                    while (true){
                        touchwin(scr->subwindow.itemDescriptionWindow);
                        wborder(scr->subwindow.itemDescriptionWindow,0,0,0,0,0,0,0,0);
                        if (activeWindow==0){
                            for (int i=0;i<inventory.size();i++){
                                if (inventory[i]->selected==true){
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,0,10,inventory[i]->name.c_str());
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,1,1,inventory[i]->itemDescription().c_str());
                                }
                            }
                        }
                        wrefresh(scr->subwindow.itemDescriptionWindow);

                    }
                    if (activeWindow==0){
                        inventory[itemSelected]->selected=false;
                    }
                }
            }
        }


        erase();


    }
}

void player::examineGround(screen* scr, std::vector<item*> *itemsExamining,coordinate spotExamining)
{
    touchwin(scr->subwindow.examineWindow);
    wborder(scr->subwindow.examineWindow,0,0,0,0,0,0,0,0);
    char ch;
    int itemSelected=0;

    while (true){
        mvwaddstr(scr->subwindow.examineWindow,0,5,"items");
        for (int i=0;i<scr->subwindow.height();i++){

            if (i==itemsExamining->size()){
                break;
            }

            for (int j=0;j<itemsExamining->size();j++){
                if (coordinate(((*itemsExamining)[j]->x),(*itemsExamining)[j]->y)==spotExamining){
                    if ((*itemsExamining)[i]->selected==false){
                        mvwaddch(scr->subwindow.examineWindow,i+1,1,'-');
                    }
                    else{
                        mvwaddch(scr->subwindow.examineWindow,i+1,1,'+');
                    }
                    if (i == itemSelected){
                        wattron(scr->subwindow.examineWindow,A_REVERSE);
                    }
                    mvwaddstr(scr->subwindow.examineWindow,i+1,2,(*itemsExamining)[i]->name.c_str());
                    wattroff(scr->subwindow.examineWindow,A_REVERSE);
                }
            }

        }
        wrefresh(scr->subwindow.examineWindow);
        ch=wgetch(scr->subwindow.examineWindow);
        for (int i=0;i<16;i++){
            if (ch==numpadControls[i] or ch==VIKEYSControls[i] or ch==keyBrdControls[i]){
                if (i==0){
                   if (itemSelected-1>=0){
                        itemSelected--;
                    }
                }
                else if (i==2){
                    if (itemSelected+1<(*itemsExamining).size()){
                        itemSelected++;
                    }
                }
                else if (i==3){
                    (*itemsExamining)[itemSelected]->selected=true;
                }
                else if (i==4){
                    (*itemsExamining)[itemSelected]->selected=false;
                }
                else if (i==15){
                    bool unloadedItem;
                    int wait=0;
                    int temp=(*itemsExamining).size();
                    while (true){
                        unloadedItem=false;
                        for (int j=0;j<(*itemsExamining).size();j++){
                            if ((*itemsExamining)[j]->selected==true){
                                (*itemsExamining)[j]->selected=false;
                                inventory.push_back((*itemsExamining)[j]);
                                (*itemsExamining).erase((*itemsExamining).begin()+j);
                            }
                            wait++;
                        }
                        if (wait==temp){
                            break;
                        }
                    }
                    werase(scr->subwindow.examineWindow);
                    refresh();
                    return;
                }
            }
        }
    }
}
