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

void monster::movement(std::vector<std::vector<tile*> > *_map,std::vector<item*> *localItems, std::vector<actor*> actors,  sf::RenderWindow &window, bool &keyrelease)
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



    //to actually commence AI movement and things:
    if (counter==5){//if there's no path:

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
        //if you have a path:
        if (path.size()>0)
        {
            //if an enemy is adjacent, attack them and set attacking to true.
            for (actor* _a : actors){
                if (coordinate(_a->col(),_a->row())==coordinate(path[path.size()-1].x,path[path.size()-1].y)){
                    attackEnemy(_a, _map);
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

        sprite.setPosition(x*16,y*16);
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

void player::movement(std::vector<std::vector<tile*> > *_map,std::vector<item*> *localItems, std::vector<actor*> actors, sf::RenderWindow &window, bool &keyrelease)
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
    int ch;
    coordinate temp = coordinate(x,y);
    bool moveThroughDoor=true;
    bool attacking=false;
    bool pressedKey = false;
    char inventoryMovement;
    char closeDirection;
    char examineDirection;
    std::vector<item*> itemsExamining;

    sf::Event event;

    tile tempFuckdebugging;
    coordinate tempShit=coordinate(x,y);
    customSpeed=speed();
    while (counter>=customSpeed and keyrelease == true){

            while (pressedKey == false){
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::KeyPressed){
                        pressedKey = true;
                    }
                }
            }
            pressedKey = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){openInventory(window,localItems);}
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                while (pressedKey == false){
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::KeyPressed){
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                            pressedKey = true;
                        }
                    }
                }
                (*_map)[temp.y][temp.x]->interactWithDoor(false);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                while (pressedKey == false){
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::KeyPressed){
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){temp.y--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){temp.y++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){temp.y++;temp.x++;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){temp.y++;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){temp.y--;temp.x--;keyrelease=false;}
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){temp.y--;temp.x++;keyrelease=false;}
                            pressedKey = true;
                        }
                    }
                }
                std::cout << "Here\n";
//                for (item* _i : localItems){
//                    if (coordinate(_i->x,_i->y) == temp){itemsExamining.push_back(_i);}
//                }
                examineGround(window,localItems,temp);
            }
            else if ((*_map)[temp.y][temp.x]->movementCost!=-1){
                if ((*_map)[temp.y][temp.x]->isDoor){
                    moveThroughDoor = (*_map)[temp.y][temp.x]->interactWithDoor(true);
                }
                if (moveThroughDoor == true){
                    pos(temp.y,temp.x);
                    counter=0;
                }
            }


        sprite.setPosition(x*16,y*16);
    }
    counter++;
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

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    texture = RSL::getTextureData(fileName,speciesToLoad+".texture");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity");
    body = RSL::getBodyData(fileName, speciesToLoad+".limbs");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");


    sprite.setTexture(texture);


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

    species = RSL::getStringData(fileName,speciesToLoad+".name");
    texture = RSL::getTextureData(fileName, speciesToLoad+".texture");
    description = RSL::getStringData(fileName, speciesToLoad+".description");
    attack = RSL::getIntData(fileName, speciesToLoad+".strength");
    dexterity = RSL::getIntData(fileName, speciesToLoad+".dexterity");
    body = RSL::getBodyData(fileName, speciesToLoad+".limbs");
    hairColor = RSL::getStringData(fileName,speciesToLoad+".hairColor");
    eyeColor = RSL::getStringData(fileName, speciesToLoad+".eyeColor");

    sprite.setTexture(texture);

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
