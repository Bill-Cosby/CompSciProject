#include "menu.h"

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
