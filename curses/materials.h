#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <vector>
#include <curses.h>

#define NUMBER_OF_COLORS 13

#include <SFML/Graphics.hpp>

#define wood 9
#define stone 10
#define iron 11
#define grass 12


class material
{
    public:
    sf::Texture texture;
    std::string name;
};

void declareColors();


#endif // MATERIALS_H_INCLUDED
