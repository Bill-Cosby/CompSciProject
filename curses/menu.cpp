#include "menu.h"

mainMenu::mainMenu(std::string title,bool _v, int _p)
{
    buffer.loadFromFile("zipclick.flac");
    sound.setBuffer(buffer);
    verticle = _v;
    percentOfScreen=_p;
    quit_game=false;
    buttonSelected=false;
    if (title=="Main Menu"){
        listOfButtons.push_back(menu_button("","Numpad or WASD for movement \n enter or 5 for selection"));
        listOfButtons.push_back(menu_button("New Game","Start a new game"));
        listOfButtons.push_back(menu_button("Load Game", "Load a previous game **CURRENTLY SERVES NO PURPOSE**"));
        listOfButtons.push_back(menu_button("New World", "Generate a new world **CURRENTLY SERVES NO PURPOSE**"));
        listOfButtons.push_back(menu_button("Options", "**CURRENTLY SERVES NO PURPOSE**"));
        listOfButtons.push_back(menu_button("Quit", "Exit Game"));
        listOfButtons[0].selected=true;
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
    int menuSelector=0;
    int position=1;
    char ch;

    while (buttonSelected==false){
        if (verticle==true and ch=='2' or verticle==false and ch=='6'){
        erase();
            if (menuSelector+1<listOfButtons.size()){
                    listOfButtons[menuSelector].selected=false;
                    menuSelector++;
                    sound.play();
                }
                ch=='0';
        }
        else if(verticle==true and ch=='8' or verticle==false and ch=='4'){
        erase();
            if (menuSelector-1>=0){
                listOfButtons[menuSelector].selected=false;
                menuSelector--;
                sound.play();
            }
            ch=='0';
        }
        else if (ch==10 or ch=='5'){
            for (int i=0;i<listOfButtons.size();i++){
                if (listOfButtons[i].selected==true){
                    if (listOfButtons[i].name == "New Game")
                    {
                        buttonSelected=true;
                    }
                    else if (listOfButtons[i].name == "Load Game")
                    {
                        buttonSelected=true;
                    }
                    else if (listOfButtons[i].name == "Quit"){
                        buttonSelected = true;
                        quit_game = true;
                    }
                }
            }
        }




        listOfButtons[menuSelector].selected=true;


        for (menu_button _b : listOfButtons){
            wborder(scr.win,0,0,0,0,0,0,0,0);
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
                    mvwaddstr(scr.win,_b.y-10,_b.x,_b.description.c_str());

                    attron(A_REVERSE);
                }
            }

            mvwaddstr(scr.win,_b.y,_b.x,_b.name.c_str());
            attroff(A_REVERSE);
            wrefresh(scr.win);
        }
        position=1;
        refresh();
        ch=wgetch(scr.win);

    }

}
