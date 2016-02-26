#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <vector>

#define NUMBER_OF_COLORS 13

#include "RSL.h"
#include <SFML/Graphics.hpp>

const sf::Color  ironColor  = sf::Color(sf::Color(197,103,41));
const sf::Color steelColor  = sf::Color(sf::Color(180,184,187));
const sf::Color  woodColor  = sf::Color(sf::Color(156,94,47));
const sf::Color copperColor = sf::Color(sf::Color(188,84,31));
const sf::Color stoneColor  = sf::Color (sf::Color(128,128,128));

const sf::Color whiteSkinColor = sf::Color(sf::Color(242,221,220));
const sf::Color brownSkinColor = sf::Color(sf::Color(109,70,0));
const sf::Color  tanSkinColor  = sf::Color(sf::Color(173,109,0));
const sf::Color greenSkinColor = sf::Color(sf::Color(51,109,0));
const sf::Color blackSkinColor = sf::Color(sf::Color(0,0,0));

const sf::Texture wall = RSL::getTextureData("data/textures/tiles.raw","wall.texture");
const sf::Texture floortex = RSL::getTextureData("data/textures/tiles.raw","floor.texture");
const sf::Texture openDoor = RSL::getTextureData("data/textures/tiles.raw","opendoor.texture");
const sf::Texture closedDoor = RSL::getTextureData("data/textures/tiles.raw","door.texture");

class material
{
    public:
    sf::Color color;
    int weight;
    material(std::string mat_name);
};



#endif // MATERIALS_H_INCLUDED
