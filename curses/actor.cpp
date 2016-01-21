#include "actor.h"
#include <cstdlib>

    char numpadControls[17] = {'8','5','2','6','4','7','9','3','1','c','o','i',27,'@','e','5','x'};
    char keyBrdControls[17] = {'w','.','s','d','a',-1,-1,-1,-1,'c','o','i',27,'@','e',10,'x'};
    char VIKEYSControls[17] = {'h','.','j','l','k','y','u','m','n','c','o','i',27,'@','e',10,'x'};
    coordinate directions[9] = {coordinate(0,-1),coordinate(0,0),coordinate(0,1),coordinate(1,0),coordinate(-1,0),coordinate(-1,-1),coordinate(1,-1),coordinate(1,1),coordinate(-1,1)};
const short int numberOfControls = 16;



void actor::makeCorpse( std::vector<item*> *globalItems, std::vector<item*> *localItems)
{
    std::string temp = name + "'s corpse";
    globalItems->push_back(new corpse(temp,equipment,_symbol,col(),row()));
    localItems->push_back((*globalItems)[globalItems->size()-1]);
    delete this;
}

void actor::dodgeAttack(actor* enemyDodgingFrom, std::vector<std::vector<tile*> > *_map)
{
    coordinate dodgeDirection(x-enemyDodgingFrom->col(),y-enemyDodgingFrom->row());
    bool dodged=false;
    coordinate temp=coordinate(x,y);
    if (y+dodgeDirection.y>=0 and y+dodgeDirection.y<(*_map).size() and (*_map)[y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
        if (x+dodgeDirection.x>=0 and x+dodgeDirection.x<(*_map).size() and (*_map)[y][x+dodgeDirection.x]->movementCost!=-1){
            x+=dodgeDirection.x;
        }
        dodged=true;
    }
        dodgeDirection.y*=-1;
        dodgeDirection.x*=-1;
    if(dodged==false and !(coordinate(x,y+dodgeDirection.y)==coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and y+dodgeDirection.y>=0 and y+dodgeDirection.y<(*_map).size() and (*_map)[y+dodgeDirection.y][x]->movementCost!=-1){
        y+=dodgeDirection.y;
    }
    else if (dodged==false and !(coordinate(x+dodgeDirection.x,y)!=coordinate(enemyDodgingFrom->col(),enemyDodgingFrom->row())) and x+dodgeDirection.x>=0 and x+dodgeDirection.x<(*_map).size() and (*_map)[y][x+dodgeDirection.x]->movementCost!=-1){
        x+=dodgeDirection.x;
    }
    if (temp==coordinate(x,y)){
        if (dodgeDirection.y==0 and (*_map)[y+1][x]->movementCost!=-1){
            y+=1;
        }
        else if (dodgeDirection.y==0 and (*_map)[y--][x]->movementCost!=-1){
            y+=-1;
        }
        else if (dodgeDirection.x==0 and (*_map)[y][x+1]->movementCost!=-1){
            x+=1;
        }
        else if (dodgeDirection.x==0 and (*_map)[y][x--]->movementCost!=-1){
            x+=-1;
        }
    }
}

void actor::attackEnemy(actor* enemyAttacking, std::vector<std::vector<tile*> > *_map)
{
    srand(time(NULL));
    srand(rand()%time(NULL));
    srand(rand()%rand()%time(NULL));
    if (rand()%100<accuracy and enemyAttacking->name!=name){
        //enemyAttacking->health-=attack-enemyAttacking->defense;
    }
    else if (enemyAttacking->name!=name){
        enemyAttacking->dodgeAttack(this,_map);
    }
}

bool monster::canSee(std::vector<std::vector<tile*> > _map, coordinate checkSpot)
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
            if (_map[y1][x1]->movementCost==-1 or (_map[y1][x1]->isDoor==true and _map[y1][x1]->isOpen()==false)){
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
            if (_map[y1][x1]->movementCost==-1 or (_map[y1][x1]->isDoor==true and _map[y1][x1]->isOpen()==false)){
                return false;
            }
        }
    }
    return true;
}

void monster::movement(std::vector<std::vector<tile*> > *_map,std::vector<item*> *localItems, std::vector<actor*> actors,  screen* scr)
{

    //initialize the goal to not be used
    coordinate goal(-1,-1);

    //raise the monster's counter by 1
    counter++;

    //we aren't initially attacking anything (stateless AI)
    bool attacking=false;

    //not currently used until we find a better method
    std::vector<coordinate> noGo;

    //if you're evil and you see someone of a different species, they're your target
    for (actor* _a : actors){
        noGo.push_back(coordinate(_a->col(),_a->row()));
        if (EVIL==true and species!=_a->species and canSee(*_map,coordinate(_a->col(),_a->row()))){
            goal = coordinate(_a->col(),_a->row());
            memory=goal;
        }
    }

    // if you can see your goal, make a path to it.
    if (canSee(*_map,goal))
    {
        path = pathFinder(*_map,coordinate(col(),row()),goal,noGo);
    }

    //if there's no path:
    if (path.size()== 0)
    {

        //if you have no memory:
        if (memory.x!=-1 and memory.y!=-1)
        {
            path=pathFinder(*_map,coordinate(col(),row()),memory,noGo);
            memory=coordinate(-1,-1);
        }

        //if your position isn't your post and you have a post
        else if (coordinate(x,y) != post and post!=coordinate(-1,-1)){
            path=pathFinder(*_map,coordinate(col(),row()),post,noGo);
        }
    }

    //to actually commence AI movement and things:
    if (counter==5)
    {
        //if you have a path:
        if (path.size()>0)
        {
            //if an enemy is adjacent, attack them and set attacking to true.
            for (actor* _a : actors){
                if (coordinate(_a->col(),_a->row())==coordinate(path[path.size()-1].x,path[path.size()-1].y)){
                    attackEnemy(_a, _map);
                    scr->addAnnouncement(species + " attacks " + _a->species);
                    attacking=true;
                }
            }
            //if you aren't attacking anyone, move along your path.
            if (attacking==false){
                moveOnPath(*_map);
            }

        }
        //reset the counter to 0
        counter=0;
    }
    return;
}

void monster::moveOnPath(std::vector<std::vector<tile*> >_map)
{
    if (path.size()!=0){
        pos(path[path.size()-1].y,path[path.size()-1].x);
        path.erase(path.begin()+path.size()-1);
    }
}

void player::movement(std::vector<std::vector<tile*> > *_map,std::vector<item*> *localItems, std::vector<actor*> actors, screen* scr)
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
    16 = LOOK
    */
    char ch;
    bool moveThroughDoor=true;
    bool attacking=false;
    char inventoryMovement;
    char closeDirection;
    char examineDirection;

    tile tempFuckdebugging;
    coordinate tempShit=coordinate(x,y);
    customSpeed=speed();
    if (counter==customSpeed){
        ch=wgetch(scr->subwindow.sub);
        for (int i=0;i<numberOfControls;i++){

            if (ch==numpadControls[i] or ch==keyBrdControls[i] or ch==VIKEYSControls[i]){

                if (i<9){

                    if ((*_map)[y+directions[i].y][x+directions[i].x]->movementCost!=-1){

                        for (actor* _a : actors){
                            if (coordinate(_a->col(),_a->row())==coordinate(x+directions[i].x,y+directions[i].y)){
                                attacking=true;
                                attackEnemy(_a,_map);
                            }
                        }
                        if (attacking!=true){
                            if ((*_map)[y+directions[i].y][x+directions[i].x]->isDoor==true){
                                moveThroughDoor=(*_map)[y+directions[i].y][x+directions[i].x]->interactWithDoor(true);
                            }
                            if (moveThroughDoor==true or (*_map)[y+directions[i].y][x+directions[i].x]->isDoor==false){
                                y+=directions[i].y;
                                x+=directions[i].x;
                            }
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

                            (*_map)[y+directions[i].y][x+directions[i].x]->interactWithDoor(opening);
                        }
                    }
                }
                if (i == 14){
                    examineDirection = wgetch(scr->subwindow.sub);
                    for (int i=0;i<9;i++){
                        if (examineDirection==numpadControls[i] or examineDirection==keyBrdControls[i] or examineDirection==VIKEYSControls[i]){
                            examineGround(scr, localItems, coordinate(directions[i].x+x,directions[i].y+y));
                        }
                    }

                }
                if (i == 11){
                    openInventory(scr, localItems);
                }

            }
        }
        counter=0;
    }
    counter++;
}

void player::openInventory(screen* scr, std::vector<item*> *localItems)
{
    bool activeWindow=0; //0 means inventory, not equipment
    bool examiningItem=true;
    bool inventoryOpen=true;
    int itemSelected=0;
    int buttonSelected=0;
    char ch=-1;
    while (inventoryOpen==true){
//=============INVENTORY/EQUIPMENT MENU=========================
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
        for (int i=0;i<numberOfControls;i++){
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

                if (i == 12){
                    inventoryOpen=false;
                }

                if (i==1 or i==15){
                    examiningItem=true;
                    if (activeWindow==0){
                        inventory[itemSelected]->selected=true;
                    }
                    else{
                        equipment[itemSelected]->selected=true;
                    }
                    while (examiningItem==true){
//=====================EXAMINE ITEM MENU===========================================
                        touchwin(scr->subwindow.itemDescriptionWindow);
                        wborder(scr->subwindow.itemDescriptionWindow,0,0,0,0,0,0,0,0);
                        std::vector<std::string> listOfButtons;
                        if (activeWindow==0){
                            for (int j=0;j<inventory.size();j++){
                                if (inventory[j]->selected==true){
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,0,10,inventory[j]->name.c_str());
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,1,1,inventory[j]->itemDescription().c_str());
                                    listOfButtons.push_back("Equip");
                                    listOfButtons.push_back("Use");
                                    listOfButtons.push_back("Drop");
                                }
                            }
                        }
                        else{
                            for (int j=0;j<equipment.size();j++){
                                if (equipment[j]->selected==true){
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,0,10,equipment[j]->name.c_str());
                                    mvwaddstr(scr->subwindow.itemDescriptionWindow,1,1,equipment[j]->itemDescription().c_str());
                                    listOfButtons.push_back("Unequip");
                                    listOfButtons.push_back("Use");
                                    listOfButtons.push_back("Drop");
                                }
                            }
                        }
                        for (int j=0;j<listOfButtons.size();j++){
                            if (j==buttonSelected){
                                wattron(scr->subwindow.itemDescriptionWindow, A_REVERSE);
                            }
                            mvwaddstr(scr->subwindow.itemDescriptionWindow,j+5,30,listOfButtons[j].c_str());
                            wattroff(scr->subwindow.itemDescriptionWindow, A_REVERSE);
                        }
                        wrefresh(scr->subwindow.itemDescriptionWindow);

                        ch=wgetch(scr->subwindow.itemDescriptionWindow);
                        werase(scr->subwindow.itemDescriptionWindow);
                        for (int j=0;j<numberOfControls;j++){
                            if (ch==numpadControls[j] or ch==keyBrdControls[j] or ch==VIKEYSControls[j]){
                                if (j==12){
                                    examiningItem=false;
                                }
                                if (j==0){
                                    if (buttonSelected-1>=0){
                                        buttonSelected--;
                                    }
                                }
                                if (j==2){
                                    if (buttonSelected+1<=listOfButtons.size()){
                                        buttonSelected++;
                                    }
                                }
                                if (j==1){
                                    if (listOfButtons[buttonSelected]=="Equip"){
                                        inventory[itemSelected]->selected=false;
                                        equipment.push_back(inventory[itemSelected]);
                                        inventory.erase(inventory.begin()+itemSelected);
                                        defense+=inventory[itemSelected]->defense;
                                        attack+=inventory[itemSelected]->attack;


                                        for (bodyPart* _b : body){
                                            if (_b->hasHand() == equipment[equipment.size()-1]->locationOnBody){
                                                _b->equip(equipment[equipment.size()-1], true);
                                                std::string temp = "You equipped a " +equipment[equipment.size()-1]->name + " in your " + _b->hasHand();
                                                scr->addAnnouncement(temp);
                                            }
                                        }
                                    }
                                    if (listOfButtons[buttonSelected]=="Unequip"){
                                        inventory[itemSelected]->selected=false;
                                        inventory.push_back(equipment[itemSelected]);
                                        equipment.erase(equipment.begin()+itemSelected);
                                        defense-=equipment[itemSelected]->defense;
                                        attack-=equipment[itemSelected]->attack;
                                    }
                                    if (listOfButtons[buttonSelected]=="Use"){
                                        if (activeWindow==0){
                                            //inventory[itemSelected]->use();
                                        }
                                        if (activeWindow==1){
                                            //equipment[itemSelected]->use();
                                        }
                                    }
                                    if (listOfButtons[buttonSelected]=="Drop"){
                                        if (activeWindow==0){
                                                inventory[itemSelected]->x=x;
                                                inventory[itemSelected]->y=y;
                                            localItems->push_back(inventory[itemSelected]);
                                            inventory.erase(inventory.begin()+itemSelected);
                                        }
                                        if (activeWindow==1){
                                                equipment[itemSelected]->x=x;
                                                equipment[itemSelected]->y=y;
                                            localItems->push_back(equipment[itemSelected]);
                                            equipment.erase(equipment.begin()+itemSelected);
                                        }
                                    }
                                    examiningItem=false;
                                    ch=-1;
                                }
                                wrefresh(scr->subwindow.itemDescriptionWindow);
                            }
                        }

                    }
                    werase(scr->subwindow.equipmentWindow);
                    werase(scr->subwindow.inventoryWindow);
                    if (activeWindow==0){
                        inventory[itemSelected]->selected=false;
                    }
                }
            }
        }
    }
    werase(scr->subwindow.equipmentWindow);
    werase(scr->subwindow.inventoryWindow);
    erase();
    refresh();
}

void player::examineGround(screen* scr, std::vector<item*> *itemsExamining,coordinate spotExamining)
{
    touchwin(scr->subwindow.examineWindow);
    wborder(scr->subwindow.examineWindow,0,0,0,0,0,0,0,0);
    std::vector<item*> itemsYouFound;
    char ch;
    bool examiningGround=true;
    bool unloadedItem=false;
    for (int i=0;i<(*itemsExamining).size();i++){
        if (coordinate(((*itemsExamining)[i]->x),(*itemsExamining)[i]->y)==spotExamining){
            itemsYouFound.push_back((*itemsExamining)[i]);
        }
    }
    int itemSelected=0;

    while (examiningGround==true){
        for (int i=0;i<scr->subwindow.height();i++){

            if (i==itemsYouFound.size()){
                break;
            }
            if (itemsYouFound[i]->selected==false){
                mvwaddch(scr->subwindow.examineWindow,i+1,1,'-');
            }
            else{
                mvwaddch(scr->subwindow.examineWindow,i+1,1,'+');
            }
            if (i == itemSelected){
                wattron(scr->subwindow.examineWindow,A_REVERSE);
            }
            mvwaddstr(scr->subwindow.examineWindow,i+1,2,itemsYouFound[i]->name.c_str());
            wattroff(scr->subwindow.examineWindow,A_REVERSE);
        }
        wrefresh(scr->subwindow.examineWindow);
        ch=wgetch(scr->subwindow.examineWindow);
        for (int i=0;i<numberOfControls;i++){
            if (ch==numpadControls[i] or ch==VIKEYSControls[i] or ch==keyBrdControls[i]){
                if (i==0){
                   if (itemSelected-1>=0){
                        itemSelected--;
                    }
                }
                else if (i==2){
                    if (itemSelected+1<itemsYouFound.size()){
                        itemSelected++;
                    }
                }
                else if (i==3){
                    itemsYouFound[itemSelected]->selected=true;
                }
                else if (i==4){
                    itemsYouFound[itemSelected]->selected=false;
                }
                else if (i==12){
                    examiningGround=false;
                }
                else if (i==15){
                    int wait=0;
                    int temp=itemsYouFound.size();
                    while (true){
                        unloadedItem=false;
                        for (int j=0;j<itemsYouFound.size();j++){
                            if (itemsYouFound[j]->selected==true){
                                itemsYouFound[j]->selected=false;
                                inventory.push_back((*itemsExamining)[j]);
                                std::string temporary = "You picked up " + (*itemsExamining)[j]->name;
                                for (int k = 0; k < (*itemsExamining).size(); k++){
                                    if ((*itemsExamining)[k]==itemsYouFound[j]){
                                        (*itemsExamining).erase((*itemsExamining).begin()+k);
                                    }
                                }
                                scr->addAnnouncement(temporary);
                            }
                            wait++;
                        }
                        if (wait==temp){
                            break;
                        }
                    }
                    clear();
                    werase(scr->subwindow.examineWindow);
                    wrefresh(scr->subwindow.examineWindow);
                    bool youAintRight=false;

                    return;
                }
            }
        }
    }
}

player::player(std::string speciesToLoad)
{
    coolDown=0;
    numberOfLegs=0;
    totalWeight=0;
    accuracy=100;
    defense=0;
    counter=0;
    onGround = false;
    sprinting=false;
    controlled=true;
    sprinting=false;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".speciesName");
    _symbol = RSL::getStringData(fileName,speciesToLoad+".defaultsymbol")[0];
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    body = RSL::getBodyData(fileName, speciesToLoad+".limbs");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");

    for (bodyPart* _b : body){
        totalWeight+=_b->weight;
    }

    std::cout << "A " << totalWeight << " pound " << species << " with "<< hairColor << " hair and " << eyeColor << " eyes\n" << std::endl;
    std::cout << description << std::endl;

}

monster::monster(std::string speciesToLoad)
{
    coolDown=0;
    numberOfLegs=0;
    totalWeight=0;
    accuracy=100;
    defense=0;
    counter=0;
    onGround = false;
    sprinting=false;
    controlled=true;
    sprinting=false;

    std::string fileName = "data/creatures/creature_standard.raw";

    species = RSL::getStringData(fileName,speciesToLoad+".speciesName");
    _symbol = RSL::getStringData(fileName,speciesToLoad+".defaultsymbol")[0];
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    body = RSL::getBodyData(fileName, speciesToLoad+".limbs");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");

    for (bodyPart* _b : body){
        if (_b->hasFoot() == true){
            numberOfLegs++;
        }
        totalWeight+=_b->weight;
    }

    std::cout << "A " << totalWeight << " pound " << species << " with "<< hairColor << " hair and " << eyeColor << " eyes\n" << std::endl;
    std::cout << description << std::endl;
    controlled=false;
    sprinting=false;
    memory=coordinate(-1,-1);
    post=coordinate(-1,-1);
    path.resize(0);
}
