#include "actor.h"


bool actor::isItemBetter()
{
    float currentItemStat = NULL+1;
    float newItemStat = 0;
    bool foundItemOfSameType = false;
    newItemStat = itemToPickUp->attack + itemToPickUp->defense + itemToPickUp->health + itemToPickUp->speed + itemToPickUp->value;
    newItemStat /= 5;
    if(equipment.size() == 0)
    {
        return true;
    }
    for(item* _i : equipment){
        if (_i->type == itemToPickUp->type){
            foundItemOfSameType = true;
            currentItemStat = _i->attack + _i->defense + _i->health + _i->speed + _i->value;
            currentItemStat /= 5;
            if(currentItemStat > newItemStat)
            {
                return true;
            }
        }
    }
    if (foundItemOfSameType == false)return true;
    return false;
}

bool actor::canSee(std::vector<std::vector<std::vector<tile*> > > _map, coordinate checkSpot)
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
            if (coordinate(x1,y1) == goal)return true;
            if (_map[1][y1][x1]->movementCost==-1 or (_map[1][y1][x1]->isDoor==true and _map[1][y1][x1]->isOpen()==false)){
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
            if (coordinate(x1,y1) == goal)return true;
            if (_map[1][y1][x1]->movementCost==-1 or (_map[1][y1][x1]->isDoor==true and _map[1][y1][x1]->isOpen()==false)){
                return false;
            }
        }
    }
    return true;
}

void actor::dialogue(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, announcements & announcementList, sf::RenderWindow &window,actor* controlledActor)
{
    sf::Font font;
    font.loadFromFile("data/PressStart2P-Regular.ttf");

    sf::Text text;
    text.setFont(font);
    int questionOn = 0;
    bool answered = false;
    bool keyreleased = false;

    std::string questions[4] = {"Can you come with me?","Do you see any items nearby?","Do you see any monsters nearby?","Do you have anything I can buy?"};
    std::string temp = RSL::getStringData("data/dialogue/dialogue.raw","human.text");

    sf::Event event;

    while (1){

        window.clear(sf::Color::Black);

        text.setCharacterSize(18);
        text.setPosition(10,10);
        text.setString(name);
        window.draw(text);


        text.setPosition(10,50);
        text.setString(temp);
        text.setCharacterSize(12);

        window.draw(text);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) and keyreleased == true and answered == false){questionOn++; keyreleased = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) and keyreleased == true and answered == false){questionOn--; keyreleased = false;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true and answered == false){
            if (questionOn == 0){
                if ((rand()%100)<10){
                    temp = "Yes! That sounds like fun!";
                    actorFollowing = controlledActor;
                }
                else{
                    temp = "No, that's too dangerous.";
                }
            }
            if (questionOn == 1){
                    bool helpful = false;
                    if (actorFollowing == controlledActor){
                        if (findItem(_map,localItems) == true){
                            temp = "I see a few that are interesting";
                        }
                        else{
                            temp = "No, none that I'd consider interesting.";
                        }
                        helpful = true;
                    }
                    if (helpful == false){
                        temp = "Why would I help you?";
                    }
            }
            if (questionOn == 2){
                    bool helpful = false;
                    if (helpful == false){
                        temp = "Why would I help you?";
                    }
            }
            if (questionOn == 3){
                bool selling = false;
                for (item* _i : inventory){
                    if (_i->value >= 50){
                        selling = true;
                    }
                }
                if (selling == false){
                    temp = "I have nothing of value.";
                }
                else{
                    temp = "I have a few things, maybe.";
                }
            }
            answered = true;
            keyreleased = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) and keyreleased == true and answered == true){return;}
        if (questionOn == 4)questionOn = 0;
        if (questionOn < 0)questionOn = 3;

        while (window.pollEvent(event)){
            if (event.type ==  sf::Event::KeyReleased)keyreleased = true;
        }

        if (answered == false){
            for (int i = 0;i<4;i++){

                if (i == questionOn)text.setStyle(sf::Text::Underlined);

                text.setString(questions[i]);
                text.setPosition(50,80+i*20);
                window.draw(text);
                text.setStyle(sf::Text::Regular);

            }
        }
        else {

                text.setStyle(sf::Text::Underlined);

                text.setString("Ok.");
                text.setPosition(50,80);
                window.draw(text);
                text.setStyle(sf::Text::Regular);
        }



        window.display();
    }


}

bool actor::findPath(std::vector<std::vector<std::vector<tile*> > > &_map)
{
    if (canSee(_map,goal)){
        coordinate temp(0,0);
        if (goal.x>x)temp.x++;
        if (goal.x<x)temp.x--;
        if (goal.y>y)temp.y++;
        if (goal.y<y)temp.y--;
        path.push_back(coordinate(x+temp.x,y+temp.y));
    }
    else path = pathFinder(_map,coordinate(x,y),goal,noGo);
    if (path.size()==0){
    path.clear();
    return false;
    }
    if (path.size()>0){
        return true;
    }
}

void monster::moveOnPath(std::vector<std::vector<std::vector<tile*> > > &_map)
{
    if (path.size()!=0){
        if (!_map[1][path[path.size()-1].y][path[path.size()-1].x]->isOpen()){
            _map[1][path[path.size()-1].y][path[path.size()-1].x]->interactWithDoor(true);
            memory = coordinate(path[path.size()-1].x,path[path.size()-1].y);
            interactedWithDoor = true;
        }
        else{
            _map[1][path[path.size()-1].y][path[path.size()-1].x]->occupied = this;
            _map[1][y][x]->occupied = NULL;
            pos(path[path.size()-1].y,path[path.size()-1].x);
            path.erase(path.begin()+path.size()-1);

            if (memory != coordinate(x,y) and interactedWithDoor){
                _map[1][memory.y][memory.x]->interactWithDoor(false);
                interactedWithDoor = false;
            }
        }
    }
}
