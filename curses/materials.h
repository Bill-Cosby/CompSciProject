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
const sf::Color grassColor  = sf::Color(sf::Color(49,99,0));
const sf::Color  dirtColor  = sf::Color(sf::Color(155,118,83));

const sf::Color whiteSkinColor = sf::Color(sf::Color(242,221,220));
const sf::Color brownSkinColor = sf::Color(sf::Color(109,70,0));
const sf::Color  tanSkinColor  = sf::Color(sf::Color(173,109,0));
const sf::Color greenSkinColor = sf::Color(sf::Color(51,109,0));
const sf::Color blackSkinColor = sf::Color(sf::Color(0,0,0));

const sf::Texture stonewall = RSL::getTextureData("data/textures/tiles.raw","stonewall.texture");
const sf::Texture stonefloor = RSL::getTextureData("data/textures/tiles.raw","stonefloor.texture");
const sf::Texture openDoor = RSL::getTextureData("data/textures/tiles.raw","opendoor.texture");
const sf::Texture closedDoor = RSL::getTextureData("data/textures/tiles.raw","door.texture");
const sf::Texture woodwall = RSL::getTextureData("data/textures/tiles.raw","woodwall.texture");
const sf::Texture woodfloor = RSL::getTextureData("data/textures/tiles.raw","woodfloor.texture");
const sf::Texture grassGround = RSL::getTextureData("data/textures/tiles.raw","grass.texture");
const sf::Texture dirtGround = RSL::getTextureData("data/textures/tiles.raw","dirt.texture");


class material
{
    public:
    int weight;

};

sf::Color giveColor(std::string mat_name);
sf::Texture giveTexture(char dc);



#endif // MATERIALS_H_INCLUDED
