#include "menu.h"

mainMenu::mainMenu(std::string title,bool _v, int _p)
{
    if (title=="Main Menu"){
        listOfButtons.push_back(menu_button("New Game","Start a new game"));
        listOfButtons.push_back(menu_button("Load Game", "Load a previous game"));
        listOfButtons.push_back(menu_button("New World", "Generate a new world"));
        listOfButtons.push_back(menu_button("Options", "Options menu"));
        listOfButtons.push_back(menu_button("Quit"));
        listOfButtons[0].selected=true;
        verticle = _v;
        percentOfScreen=_p;
    }
}

menu_button::menu_button(std::string _title)
{
    name=_title;
    clicked=false;
    selected=false;
}

menu_button::menu_button(std::string _title, std::string _description)
{
    name=_title;
    description = _description;
    clicked=false;
    selected=false;
}

void mainMenu::mainMenuLoop(screen scr)
{
    touchwin(scr.win);
    char ch=wgetch(scr.win);
    int menuSelector=0;
    int position=1;

    while (true){
        ch=wgetch(scr.win);
        if (verticle==true and ch=='2' or verticle==false and ch=='6'){
            if (menuSelector+1<listOfButtons.size()){
                    listOfButtons[menuSelector].selected=false;
                    menuSelector++;
                }
                ch=='0';
        }
        if(verticle==true and ch=='8' or verticle==false and ch=='4'){
            if (menuSelector-1>=0){
                listOfButtons[menuSelector].selected=false;
                menuSelector--;
            }
            ch=='0';
        }
        listOfButtons[menuSelector].selected=true;
        for (menu_button _b : listOfButtons){
            if (verticle==true){
                _b.y=position;
                _b.x=10;
                position+=scr.height()/listOfButtons.size();

                if (_b.selected==true){
                    mvwaddstr(scr.win,10,scr.width()-50,_b.description.c_str());

                    attron(A_REVERSE);
                }
            }
            else
            {
                _b.y=scr.height()-10;
                _b.x=position;
                position+=scr.width()/listOfButtons.size();

                if (_b.selected==true){
                    std::cout << _b.name << std::endl;
                    mvwaddstr(scr.win,_b.y-10,_b.x,_b.description.c_str());

                    attron(A_REVERSE);
                }
            }

            mvwaddstr(scr.win,_b.y,_b.x,_b.name.c_str());
            attroff(A_REVERSE);
        }
        //erase();
        refresh();

    }

}
